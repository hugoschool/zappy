#pragma once

#include "INetwork.hpp"
#include <memory>
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
            std::unique_ptr<INetwork> _socket;

            std::string checkFd();
            std::string readMessage();

    };

}
