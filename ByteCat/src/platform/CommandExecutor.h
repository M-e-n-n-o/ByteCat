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
                m_wrappedObject(std::make_shared<Command<T>>(std::forward<T>(obj))) { }

            struct CommandBase
            {
                virtual void operator()() const = 0;
                virtual ~CommandBase() = default;
            };

            template<typename T>
            struct Command : public CommandBase
            {
                Command(const T& t) :
                    m_wrappedObject(t) {}

                ~Command() = default;

                void operator()() const override
                {
                    return m_wrappedObject();
                }
                T m_wrappedObject;
            };

            void operator()() const
            {
                return (*m_wrappedObject)();
            }

            std::shared_ptr<CommandBase> m_wrappedObject;
        };

		
		class CommandExecutor
		{
		private:			
            static inline ThreadSafeQueue<CommandWrapper>* s_commands;
		
		public:
			static void Start(bool multithreaded);

            static void PushCommand(const CommandWrapper& wrappedCommand);

            static void Sync();

            static void Shutdown();
		};
	}
}
