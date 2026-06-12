#pragma once

#include "Player.hpp"
#include <map>
#include <queue>
#include <string>

namespace zappy {
    class GameplayEntitiesHolder {
        private:
            std::map<int, PlayerInfo> _players;
            std::queue<std::pair<int, std::string>> _broadcast;
        public:
            GameplayEntitiesHolder();
            ~GameplayEntitiesHolder();

            void addMessage(int, std::string);
            void popMessage();
            std::queue<std::pair<int, std::string>> getBroadcast();

            void addPlayer(int, PlayerInfo);
            PlayerInfo& getPlayer(int);
            void removePlayer(int);
            std::map<int, PlayerInfo>& getPlayers();
    };
}