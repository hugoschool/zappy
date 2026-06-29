#pragma once

#include "IEntity.hpp"
#include <memory>

namespace zappy {
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void initWindow() = 0;
            virtual void initCamera() = 0;
            virtual bool run() = 0;
            virtual void drawTiles() = 0;
            virtual void displayTileInfo(tileCoordinates) = 0;
            virtual void displayBroadcast() = 0;
            virtual void drawPlayers() = 0;
            virtual void drawGEHInfos() = 0;
            virtual void drawLowObject() = 0;
            virtual void displayGameInfos() = 0;
            virtual void drawLowObjectTiles() = 0;
            virtual void drawLowObjectPlayers() = 0;
            virtual void handleLowObjectInputs() = 0;
            virtual void displayLowObjectTileInfo(tileCoordinates) = 0;
            virtual void displayLowObjectGameInfos() = 0;
            virtual void displayLowObjectBroadcast() = 0;
            virtual void drawLowObjectEntity(std::shared_ptr<IEntity> &, const std::pair<int, int> &) = 0;
            virtual void drawEntity(std::shared_ptr<IEntity> &, const std::pair<int, int> &) = 0;

            virtual bool endScreen(std::string) = 0;
    };
}
