#pragma once

#include "IEntity.hpp"
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
#include <Text.hpp>
#include <Shader.hpp>
#include "ModelHolder.hpp"
#include "RaylibParticles.hpp"

namespace zappy {
    constexpr float TICK_TO_CAMERA_TARGET = 60;
    class RaylibGraphical : public IGraphical {
        private:
            Map &_map; // copy the map from the communication object
            raylib::Window _window;
            raylib::Camera _camera;
            ModelHolder _modelHolder;
            Vector3 _cameraTargetTarget;
            float _tickUntilCameraTarget;
            std::map<tileCoordinates, RaylibParticles> _particles;
        public:
            RaylibGraphical() = delete;
            RaylibGraphical(Map &map);
            ~RaylibGraphical();

            void initWindow() override;
            void initCamera() override;
            bool run() override;
            void drawTiles() override;
            void drawParticles(tileCoordinates) override;
            void displayTileInfo(tileCoordinates) override;
            void drawText(std::string str, int X, int Y) override;
            // TODO maybe add in interface
            void updateCamera();
    };
}
