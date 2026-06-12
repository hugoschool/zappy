#pragma once

#include <netinet/in.h>
#include <string>
#include <sys/poll.h>

namespace zappy {
    class Socket {
        public:
            Socket() = delete;
            Socket(int port, std::string hostname);
            ~Socket();
            void Connect();
            void Close();
            int Poll(int timeout);
            std::string Receive();
            void Send(std::string msg);
            struct pollfd _pfds[1];

        private:
            int _clientSocket;
            int _port;
            struct sockaddr_in _address;
    };
}
