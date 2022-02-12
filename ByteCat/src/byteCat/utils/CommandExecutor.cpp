#include "bcpch.h"
#include "byteCat/utils/CommandExecutor.h"

namespace BC
{
	CommandExecutor::CommandExecutor(bool multithreaded)
	{
		if (m_isRunning)
		{
			return;
		}

		m_isRunning = true;

		m_commandExecutorThread = std::this_thread::get_id();

		m_isMultithreaded = multithreaded;
		if (!m_isMultithreaded)
		{
			return;
		}

		m_commands = new ThreadSafeQueue<CommandWrapper>();

		while (m_isRunning)
		{
			auto& command = m_commands->getFront();
			command();
			bool empty = m_commands->pop();

			if (empty)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_condition.notify_one();
			}
		}

		delete m_commands;
	}

	CommandExecutor::~CommandExecutor()
	{
		delete m_commands;
	}


	void CommandExecutor::pushCommand(const CommandWrapper& wrappedCommand)
	{			
		if (!m_isMultithreaded || !m_isRunning || m_commandExecutorThread == std::this_thread::get_id())
		{
			wrappedCommand();
			return;
		}
		
		m_commands->enqueue(wrappedCommand);
	}

	void CommandExecutor::sync()
	{
		if (!m_isMultithreaded || !m_isRunning)
		{
			return;
		}
		
		std::unique_lock<std::mutex> lock(m_mutex);
		while (!m_commands->isEmpty())
		{
			m_condition.wait(lock);
		}
	}

	void CommandExecutor::shutdown()
	{			
		if (!m_isMultithreaded || !m_isRunning)
		{
			return;
		}

		m_isRunning = false;
		m_commands->enqueue([]() {});
	}
}
