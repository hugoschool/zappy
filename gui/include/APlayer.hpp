#pragma once

#include "IEntity.hpp"
#include "IPlayer.hpp"
#include <string>

namespace zappy {
    class APlayer : public IPlayer {
        public:
            APlayer() = delete;
            APlayer(int id, tileCoordinates, std::string, PlayerType);
            ~APlayer();

            tileCoordinates getPos() override;
            std::string getTeamName() override;

            tileCoordinates getCoords() override;
            floatCoordinates getDisplayCoords() override;

            void updatePos(tileCoordinates, int) override;
            PlayerType getType() override;

            int getId() override;

        protected:
            tileCoordinates _pos;
            floatCoordinates _displayPos;
            std::string _teamName;
            PlayerType _type;
            int _id;
    };
}
