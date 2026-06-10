#pragma once

#include "SafeQueue.hpp"
#include "Socket.hpp"
#include <string>
#include <vector>

namespace zappy {

    class Communication {
        public:
            Communication() = delete;
            Communication(int port, std::string hostname, bool &exit, SafeQueue<std::vector<std::string>> &);
            ~Communication();

            void SocketLoop();

        private:
            Socket _socket;

            bool &_exit;

            SafeQueue<std::vector<std::string>> &_safeQueue;

            void UpdateFd(int i);
            void ReadMessage();
            void ParseMessage(std::string msg);

    };

}
