#pragma once

#include "CircularBuffer.hpp"
#include "Communication.hpp"
#include <string>

namespace zappy {
    class PlayerCommunication {
        public:
            PlayerCommunication() = delete;
            PlayerCommunication(int port, std::string hostname, bool &exit, CircularBuffer<std::string> &queue);
            ~PlayerCommunication();

            void communicationLoop();

            void parseMessages(std::string msg);
            void connect();


        private:
            Communication _communication;
            CircularBuffer<std::string> &_circularBuffer;

            bool &_exit;

            int _port;
            std::string _hostname;

            std::string _teamName;

        };
}
