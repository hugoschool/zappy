#pragma once

#include "IGraphical.hpp"
#include "Map.hpp"
#include <Color.hpp>
#include <Rectangle.hpp>
#include <Functions.hpp>
#include <Window.hpp>

namespace zappy {
    class RaylibGraphical : public IGraphical {
        private:
            Map &_map; // copy the map from the communication object
            raylib::Window _win;
        public:
            RaylibGraphical() = delete;
            RaylibGraphical(Map &map);
            ~RaylibGraphical();

            void initWindow() override;
            void loop() override;
            void drawMap() override;
            void drawTiles() override;
            void drawText(std::string str, int X, int Y) override;
    };
}
