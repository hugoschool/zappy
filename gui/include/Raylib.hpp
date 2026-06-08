#pragma once

#include "IGraphical.hpp"
#include "Map.hpp"
#include <Camera3D.hpp>
#include <Color.hpp>
#include <Rectangle.hpp>
#include <Functions.hpp>
#include <Window.hpp>
#include <Model.hpp>
#include <Mesh.hpp>
#include <Texture.hpp>
#include <vector>

namespace zappy {

    constexpr int textNums[6] = {3, 6, 2, 0, 4, 1};

    class RaylibGraphical : public IGraphical {
        private:
            Map &_map; // copy the map from the communication object
            raylib::Window _window;
            raylib::Camera _camera;
            raylib::Model _materialModel;
            std::vector<raylib::Texture2D> _materialTextures;
        public:
            RaylibGraphical() = delete;
            RaylibGraphical(Map &map);
            ~RaylibGraphical();

            void initModels() override;
            void initWindow() override;
            void initCamera() override;
            void unloadModels() override;
            void loop() override;
            void drawTiles() override;
            void drawText(std::string str, int X, int Y) override;
    };
}
