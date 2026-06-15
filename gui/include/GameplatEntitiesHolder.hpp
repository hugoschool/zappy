#pragma once

#include "Egg.hpp"
#include "Player.hpp"
#include <map>
#include <queue>
#include <string>

namespace zappy {
    class GameplayEntitiesHolder {
        private:
            std::map<int, PlayerInfo> _players;
            std::map<int , Egg> _eggs;
            std::queue<std::pair<int, std::string>> _broadcast;
        public:
            GameplayEntitiesHolder();
            ~GameplayEntitiesHolder();

            void addMessage(int, std::string);
            std::pair<int, std::string> popMessage();
            std::queue<std::pair<int, std::string>> getBroadcast();

            void addPlayer(int, PlayerInfo);
            PlayerInfo& getPlayer(int);
            void removePlayer(int);
            std::map<int, PlayerInfo>& getPlayers();

            void addEgg(int, Egg);
            Egg& getEgg(int);
            void removeEgg(int);
            std::map<int, Egg>& getEggs();

    };
}
