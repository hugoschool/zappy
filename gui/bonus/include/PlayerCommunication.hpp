#pragma once

#include "Communication.hpp"
#include "SafeQueue.hpp"
#include <string>

namespace zappy {
    class PlayerCommunication {
        public:
            PlayerCommunication() = delete;
            PlayerCommunication(int port, std::string hostname, bool &exit, SafeQueue<std::string> &queue);
            ~PlayerCommunication();

            void communicationLoop();

            void parseMessages(std::string msg);
            void connect();


        private:
            Communication _communication;
            SafeQueue<std::string> &_safeQueue;

            bool &_exit;

            int _port;
            std::string _hostname;

            std::string _teamName;

        };
}
