#pragma once

#include <algorithm>
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>

namespace zappy {
    template <typename T>
    class SafeQueue {
        private:
            std::mutex _mutex;
            std::queue<T> _safeQueue;
            std::condition_variable _conditionVariable;
            bool _terminated;
        public:
            SafeQueue() : _mutex(), _safeQueue(), _conditionVariable(), _terminated(false) {};
            ~SafeQueue() = default;

            void push(T value) {
                {
                    std::lock_guard lock(_mutex);
                    _safeQueue.push(std::move(value));
                }
                _conditionVariable.notify_one();
            }
            void pop(T &value) {
                std::unique_lock lock(_mutex);

                _conditionVariable.wait(lock, [this] { return (!_safeQueue.empty() || _terminated); });
                if (_terminated) {
                    return;
                }
                value = std::move(_safeQueue.front());
                _safeQueue.pop();
            }
            bool tryPop(T &value) {
                std::lock_guard lock(_mutex);

                if (_safeQueue.empty() == true) {
                    return false;
                } else {
                    value = std::move(_safeQueue.front());
                    _safeQueue.pop();
                    return true;
                }
            }
            void terminate(void) {
                {
                    std::lock_guard lock(_mutex);
                    _terminated = true;
                }
                _conditionVariable.notify_all();
            }
            bool isTerminated(void) {
                std::lock_guard lock(_mutex);
                return _terminated;
            }
            std::size_t size(void) {
                std::lock_guard lock(_mutex);
                return _safeQueue.size();
            }
    };
}
