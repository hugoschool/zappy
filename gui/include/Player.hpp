#pragma once

#include "APlayer.hpp"
#include "IEntity.hpp"
#include <map>
#include <string>
#include "PositionHolder.hpp"

namespace zappy {
    class PlayerInfo : public APlayer{
        public:
            PlayerInfo() = delete;
            PlayerInfo(int playerNb, tileCoordinates, int orientation, int level, std::string);
            ~PlayerInfo();

            void updatePos(tileCoordinates pos, int orientation) override final;
            int getOrientation();

            bool isIncantating();
            bool isMoving();

            void updateLevel(int newLevel);
            void updateDisplayPos();
            std::map<std::string, int> &getInventory();

            void setIncantation(bool);

        private:
            int _playerNb;
            std::vector<PositionHolder> _posVector;
            int _orientation;
            int _level;
            std::string _teamName;
            bool _isIncantating;
            bool _moving;

            std::map<std::string, int> _inventory;
    };

}
