#pragma once

#include "GameplatEntitiesHolder.hpp"
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

            GameplayEntitiesHolder _geh;

            SafeQueue<std::vector<std::string>> _commandsQueue;
            SafeQueue<std::vector<std::string>> _playerMovesQueue;

            bool _exit;

            int _timeUnit;

            Protocol _protocol;

            std::thread _protocolThread;

            void launchProtocol();
    };
}
