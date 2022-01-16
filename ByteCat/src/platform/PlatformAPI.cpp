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
				auto& command = commands.getFront();
				command();
				commands.pop();
			}
		}

		void API::PushCommand(const CommandWrapper& wrappedCommand)
		{
			commands.enqueue(wrappedCommand);
		}

		void API::Shutdown()
		{
			stop = true;

			commands.enqueue([]() {});
		}
	}
}
