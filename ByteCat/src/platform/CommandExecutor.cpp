#include "bcpch.h"
#include "platform/CommandExecutor.h"

namespace BC
{
	namespace Platform
	{
		std::atomic<bool> isRunning = false;
		std::atomic<bool> isMultithreaded = false;

		std::thread::id commandExecutorThread;
		
		std::mutex mutex;
		std::condition_variable condition;
		
		void CommandExecutor::Start(bool multithreaded)
		{			
			if (isRunning)
			{
				return;
			}
			
			isRunning = true;

			commandExecutorThread = std::this_thread::get_id();
			
			isMultithreaded = multithreaded;
			if (!isMultithreaded)
			{
				return;
			}

			s_commands = new ThreadSafeQueue<CommandWrapper>();
			
			while (isRunning)
			{
				auto& command = s_commands->getFront();
				command();
				bool empty = s_commands->pop();

				if (empty)
				{
					std::lock_guard<std::mutex> lock(mutex);
					condition.notify_one();
				}
			}

			delete s_commands;
		}

		void CommandExecutor::PushCommand(const CommandWrapper& wrappedCommand)
		{			
			if (!isMultithreaded || !isRunning || commandExecutorThread == std::this_thread::get_id())
			{
				wrappedCommand();
				return;
			}
			
			s_commands->enqueue(wrappedCommand);
		}

		void CommandExecutor::Sync()
		{
			if (!isMultithreaded || !isRunning)
			{
				return;
			}
			
			std::unique_lock<std::mutex> lock(mutex);
			while (!s_commands->isEmpty())
			{
				condition.wait(lock);
			}
		}

		void CommandExecutor::Shutdown()
		{			
			if (!isMultithreaded || !isRunning)
			{
				return;
			}

			isRunning = false;
			s_commands->enqueue([]() {});
		}
	}
}
