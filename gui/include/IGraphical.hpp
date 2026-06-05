#pragma once

#include "IEntity.hpp"
#include <string>

namespace zappy {
    class IGraphical {
        public:
            ~IGraphical() = default;

            virtual void drawMap() = 0;
            virtual void drawTile() = 0;
            virtual void drawEntities() = 0;
            virtual void drawText(std::string str, int X, int Y) = 0;
    };
}
