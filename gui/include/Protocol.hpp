#pragma once

#include "Communication.hpp"
#include "SafeQueue.hpp"
#include <vector>

namespace zappy {
    class Protocol {
        private:
            SafeQueue<std::vector<std::string>> &_safeQueue;
            Communication _communication;

            bool &_exit;

        public:
            Protocol() = delete;
            Protocol(int port, std::string hostname, bool &exit, SafeQueue<std::vector<std::string>>&);
            ~Protocol();
            void communicationLoop();
            void parseMessages(std::string msg);
            void sendCommand(std::string command);
    };
}
