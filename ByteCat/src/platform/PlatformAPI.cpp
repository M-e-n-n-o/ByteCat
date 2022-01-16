#include "bcpch.h"
#include "platform/PlatformAPI.h"

namespace BC
{
	namespace Platform
	{
		std::atomic<bool> stop = false;
		
		void API::Start()
		{
			while (!stop)
			{
				auto& command = s_executingList->getFront();
				command();
				bool empty = s_executingList->pop();
			
				if (empty)
				{
					if (s_executingList == &s_commandsFrame1)
					{
						s_executingList = &s_commandsFrame2;
					} else
					{
						s_executingList = &s_commandsFrame1;
					}
				}
			}
		}

		void API::PushCommand(const CommandWrapper& wrappedCommand)
		{
			s_pushingList->enqueue(wrappedCommand);
		}

		void API::EndFrame()
		{
			if (s_executingList == &s_commandsFrame1)
			{
				if (!s_commandsFrame2.isEmpty())
				{
					s_commandsFrame2.clear();
				}
				
				s_pushingList = &s_commandsFrame2;
			} else
			{
				if (!s_commandsFrame1.isEmpty())
				{
					s_commandsFrame1.clear();
				}

				s_pushingList = &s_commandsFrame1;
			}
		}

		void API::Shutdown()
		{
			stop = true;

			s_commandsFrame1.clear();
			s_commandsFrame2.clear();
			s_commandsFrame1.enqueue([]() {});
			s_commandsFrame2.enqueue([]() {});
		}
	}
}
