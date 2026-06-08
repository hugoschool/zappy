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
            int Poll();
            std::string Receive();
            void Send(std::string msg);

        private:
            int _clientSocket;
            int _port;
            struct sockaddr_in _address;
            struct pollfd _pfds[2];
    };
}
