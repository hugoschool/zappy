#pragma once

#include "IGraphical.hpp"
#include "Map.hpp"

namespace zappy {
    class RaylibGraphical : public IGraphical {
        private:
            Map _map;
        public:
            RaylibGraphical();
            ~RaylibGraphical();

            void drawMap() override;
            void drawTile() override;
            void drawText(std::string str, int X, int Y) override;
            void drawEntities() override;
    };
}
