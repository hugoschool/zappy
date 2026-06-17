#pragma once

#include <string>
namespace zappy {
    class INetwork {
        public:
            virtual ~INetwork() = default;

            virtual void connectSocket() = 0;
            virtual void closeSocket() = 0;

            virtual int pollConnections(int timeout) = 0;
            virtual std::string receive() = 0;
            virtual void sendMsg(std::string msg) = 0;
            virtual int updateFd() = 0;
    };
}
