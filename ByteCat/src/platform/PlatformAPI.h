#pragma once
#include <memory>
#include "byteCat/utils/ThreadSafeQueue.h"

namespace BC
{
	namespace Platform
	{
        struct CommandWrapper
        {
            template <typename T>
            CommandWrapper(T&& obj) :
                wrappedObject(std::make_shared<Command<T>>(std::forward<T>(obj))) { }

            struct CommandBase
            {
                virtual void operator()() const = 0;
                virtual ~CommandBase() = default;
            };

            template<typename T>
            struct Command : public CommandBase
            {
                Command(const T& t) :
                    wrappedObject(t) {}

                ~Command() = default;

                void operator()() const override
                {
                    return wrappedObject();
                }
                T wrappedObject;
            };

            void operator()() const
            {
                return (*wrappedObject)();
            }

            std::shared_ptr<CommandBase> wrappedObject;
        };

		
		class API
		{
		private:
            static inline ThreadSafeQueue<CommandWrapper> commands;
		
		public:
			static void Start();

            static void PushCommand(const CommandWrapper& wrappedCommand);

            static void Shutdown();
		};
	}
}
