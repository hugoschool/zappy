#pragma once

#include "GameplatEntitiesHolder.hpp"
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
            GameplayEntitiesHolder &_GEH;
            raylib::Window _window;
            raylib::Camera _camera;
            ModelHolder _modelHolder;
            Vector3 _cameraTargetTarget;
            float _tickUntilCameraTarget;
            std::map<tileCoordinates, RaylibParticles> _particles;
            std::vector<std::string> _broadcastToDisplay;
        public:
            RaylibGraphical() = delete;
            RaylibGraphical(Map &map, GameplayEntitiesHolder& GEH);
            ~RaylibGraphical();

            void initWindow() override;
            void initCamera() override;
            bool run() override;
            void drawTiles() override;
            void drawParticles(tileCoordinates) override;
            void displayTileInfo(tileCoordinates) override;
            void displayBroadcast() override;
            // Maybe get this to interface by creating a zappy::Color object that could interpret more than a raylib color
            void drawText(std::string str, int X, int Y, raylib::Color color);
            // TODO maybe add in interface
            void updateCamera();
    };
}
