#pragma once

#include "Map.hpp"
#include "Protocol.hpp"
#include "SafeQueue.hpp"
#include <string>
#include <thread>
#include <vector>

namespace zappy {
    class ZappyBonus {
        public:
            ZappyBonus() = delete;
            ZappyBonus(int port, std::string hostname);
            ~ZappyBonus();

            void loop();

        private:
            zappy::Map _map;

            SafeQueue<std::vector<std::string>> _safeQueue;

            bool _exit;

            int _timeUnit;

            Protocol _protocol;

            std::thread _protocolThread;

            void launchProtocol();
    };
}
