#pragma once

#include "CircularBuffer.hpp"
#include "Communication.hpp"
#include <string>
#include <vector>

namespace zappy {
    class Protocol {
        private:
            CircularBuffer<std::vector<std::string>> &_sendBuffer;
            CircularBuffer<std::vector<std::string>> &_receiveBuffer;
            Communication _communication;

            bool &_exit;

            int &_timeUnit;

        public:
            Protocol() = delete;
            Protocol(int port, std::string hostname, bool &exit, CircularBuffer<std::vector<std::string>>& send,
                CircularBuffer<std::vector<std::string>>& recv, int &);
            ~Protocol();
            void communicationLoop();
            void parseMessages(std::string msg);
            void sendCommand(std::string command);
    };
}
