#pragma once

#include "IEntity.hpp"
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

            virtual void updatePos() = 0;
            virtual PlayerType getType() = 0;

    };
}
