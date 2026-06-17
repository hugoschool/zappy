#pragma once

#include "ANetwork.hpp"
#include "INetwork.hpp"
#include <netinet/in.h>
#include <string>
#include <sys/poll.h>

namespace zappy {
    class Socket : public ANetwork {
        public:
            Socket() = delete;
            Socket(int port, std::string hostname);
            ~Socket();

            void connectSocket() override;
            void closeSocket() override;

            int pollConnections(int timeout) override;
            std::string receive() override;
            void sendMsg(std::string msg) override;
            stateFd updateFd() override;

        private:
            struct pollfd _pfds[1];

            int _clientSocket;
            struct sockaddr_in _address;
    };
}
