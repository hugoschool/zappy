#pragma once

#include "Socket.hpp"
#include <string>

namespace zappy {

    class Communication {
        public:
            Communication() = delete;
            Communication(int port, std::string hostname);
            ~Communication();

            std::string runSocket(int timeout);
            void sendMessage(std::string msg);

        private:
            Socket _socket;

            std::string UpdateFd(int i);
            std::string ReadMessage();

    };

}
