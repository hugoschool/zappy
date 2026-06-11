#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <map>
#include <string>

namespace zappy {
    class PlayerInfo {
        public:
            PlayerInfo() = delete;
            PlayerInfo(int playerNb, tileCoordinates, int orientation, int level, std::string);
            ~PlayerInfo();

            tileCoordinates getCoords();
            std::string getTeamName();

            bool isEgg();

            void updatePos(tileCoordinates pos, int orientation);
            void updateLevel(int newLevel);

        private:
            int _playerNb;
            tileCoordinates _pos;
            int _orientation;
            int _level;
            std::string _teamName;

            std::map<MaterialType, int> _inventory;

            bool _isEgg;

    };

}
