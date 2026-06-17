#pragma once

#include "INetwork.hpp"
#include <string>

namespace zappy {
    class ANetwork : public INetwork {
        public:
            ANetwork() = delete;
            ANetwork(int port);
            ~ANetwork();

            virtual void connectSocket() = 0;
            virtual void closeSocket() = 0;

            virtual int pollConnections(int timeout) = 0;
            virtual std::string receive() = 0;
            virtual void sendMsg(std::string msg) = 0;
            virtual stateFd updateFd() = 0;

        protected:
            int _port;
    };

}
