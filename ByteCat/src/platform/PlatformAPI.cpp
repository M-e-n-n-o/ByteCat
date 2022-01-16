#include "bcpch.h"
#include "platform/PlatformAPI.h"

namespace BC
{
	namespace Platform
	{
		std::atomic<bool> stop = false;
		std::mutex mutex;
		std::condition_variable condition;
		
		void API::Start(bool multithreaded)
		{			
			s_multithreaded = multithreaded;
			if (!s_multithreaded)
			{
				return;
			}

			s_commands = new ThreadSafeQueue<CommandWrapper>();
			
			while (!stop)
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

		void API::PushCommand(const CommandWrapper& wrappedCommand)
		{
			if (!s_multithreaded)
			{
				wrappedCommand();
				return;
			}
			
			s_commands->enqueue(wrappedCommand);
		}

		void API::Sync()
		{
			if (!s_multithreaded)
			{
				return;
			}
			
			std::unique_lock<std::mutex> lock(mutex);
			while (!s_commands->isEmpty())
			{
				condition.wait(lock);
			}
		}

		void API::Shutdown()
		{
			if (!s_multithreaded)
			{
				return;
			}
			
			stop = true;
			s_commands->enqueue([]() {});
		}
	}
}
