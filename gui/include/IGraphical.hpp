#pragma once

#include "IEntity.hpp"
#include <queue>
#include <string>

namespace zappy {
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void initWindow() = 0;
            virtual void initCamera() = 0;
            virtual bool run() = 0;
            virtual void drawTiles() = 0;
            virtual void drawParticles(tileCoordinates) = 0;
            virtual void displayTileInfo(tileCoordinates) = 0;
            virtual void displayBroadcast() = 0;
            virtual void drawPlayers() = 0;
    };
}
