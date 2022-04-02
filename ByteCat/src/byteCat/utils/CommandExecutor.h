#pragma once
#include <memory>
#include "byteCat/utils/ThreadSafeQueue.h"

namespace BC
{
    struct CommandWrapper
    {
        template <typename T>
        CommandWrapper(T&& obj): m_wrappedObject(std::make_shared<Command<T>>(std::forward<T>(obj))) { }

        struct CommandBase
        {
            virtual ~CommandBase() = default;
            virtual void operator()() const = 0;
        };

        template<typename T>
        struct Command : CommandBase
        {
            Command(const T& t): m_wrappedObject(t) {}

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
        ThreadSafeQueue<CommandWrapper>* m_commands;

        std::atomic<bool> m_isRunning = false;
        std::atomic<bool> m_isMultithreaded = false;

        std::thread::id m_commandExecutorThread;

        std::mutex m_mutex;
        std::condition_variable m_condition;
	
	public:
        CommandExecutor(bool multithreaded);
        ~CommandExecutor();

        void pushCommand(const CommandWrapper& wrappedCommand);

        void sync();

        void shutdown();
	};
}
