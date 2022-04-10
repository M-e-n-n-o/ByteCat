#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

namespace BC
{
    namespace Utils
    {
        template <class T>
        class ThreadSafeQueue
        {
        private:
            std::queue<T> m_queue;
            mutable std::mutex m_mutex;
            std::condition_variable m_condition;

        public:
            ThreadSafeQueue()
                : m_queue()
                , m_mutex()
                , m_condition()
            {}

            ~ThreadSafeQueue() {}

            // Add an element to the queue.
            void enqueue(const T& t)
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_queue.push(t);
                m_condition.notify_one();
            }

            // Get the "front"-element.
            // If the queue is empty, wait till a element is avaiable.
            T& getFront()
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                while (m_queue.empty())
                {
                    // release lock as long as the wait and reaquire it afterwards.
                    m_condition.wait(lock);
                }

                T& val = m_queue.front();

                return val;
            }

            // Returns if the queue is empty
            bool pop()
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_queue.pop();
                return m_queue.empty();
            }

            bool isEmpty()
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                return m_queue.empty();
            }

            bool getSize()
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                return m_queue.size();
            }

            void clear()
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                clear(m_queue);
            }

        private:
            void clear(std::queue<T>& q)
            {
                std::queue<T> empty;
                std::swap(q, empty);
            }
        };
    }
}
