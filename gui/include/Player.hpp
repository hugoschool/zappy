#pragma once

#include "APlayer.hpp"
#include "IEntity.hpp"
#include <map>
#include <string>

namespace zappy {
    class PlayerInfo : public APlayer{
        public:
            PlayerInfo() = delete;
            PlayerInfo(int playerNb, tileCoordinates, int orientation, int level, std::string);
            ~PlayerInfo();

            std::string getTeamName() override;

            void updatePos(tileCoordinates pos, int orientation) override;
            tileCoordinates getCoords();
            int getOrientation();

            bool isEgg();
            bool isIncantating();

            void updateLevel(int newLevel);
            std::map<std::string, int> &getInventory();

        private:
            int _playerNb;
            tileCoordinates _pos;
            int _orientation;
            int _level;
            std::string _teamName;
            bool _isIncantating;

            std::map<std::string, int> _inventory;
    };

}
