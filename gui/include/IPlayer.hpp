#pragma once

#include "IRaylibEntities.hpp"
#include <string>

namespace zappy {
    enum PlayerType {
        EGG,
        PLAYER
    };
    class IPlayer {
        public:
            virtual ~IPlayer() = default;

            virtual tileCoordinates getPos() = 0;
            virtual std::string getTeamName() = 0;

            virtual tileCoordinates getCoords() = 0;
            virtual floatCoordinates getDisplayCoords() = 0;

            virtual void updatePos(tileCoordinates, int) = 0;
            virtual PlayerType getType() = 0;
            virtual int getId() = 0;

            virtual bool getSelected() = 0;
            virtual void setSelected(bool) = 0;
    };
}
