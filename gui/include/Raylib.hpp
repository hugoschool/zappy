#pragma once

#include "GameplatEntitiesHolder.hpp"
#include "IRaylibEntities.hpp"
#include "IGraphical.hpp"
#include "Map.hpp"
#include <Camera3D.hpp>
#include <Color.hpp>
#include <Ray.hpp>
#include <Rectangle.hpp>
#include <Functions.hpp>
#include <Window.hpp>
#include <Model.hpp>
#include <Mesh.hpp>
#include <Texture.hpp>
#include <Text.hpp>
#include <Shader.hpp>
#include <RenderTexture.hpp>
#include "RaylibModelHolder.hpp"
#include "RaylibParticles.hpp"
#include "ShaderHolder.hpp"

namespace zappy {
    constexpr float TICK_TO_CAMERA_TARGET = 60;

    typedef struct {
        int fx;
        int fy;
        int sx;
        int sy;
    } highlight_values_t;

    class RaylibGraphical : public IGraphical {
        protected:
            Map &_map; // copy the map from the communication object

            GameplayEntitiesHolder &_GEH;

            raylib::Window _window;
            raylib::Camera _camera;
            RaylibModelHolder _modelHolder;
            Vector3 _cameraTargetTarget;

            float _tickUntilCameraTarget;

            std::map<tileCoordinates, RaylibParticles> _particles;

            std::vector<std::string> _broadcastToDisplay;
            std::map<std::string, raylib::Color> _colorMap;
            std::map<int, std::pair<int, int>> _playerAnimationsMap;
            std::map<int, std::pair<int, int>> _dyingPlayerAnimationsMap;
            ShaderHolder _shaderHolder;
            int _currentShader;
            raylib::RenderTexture2D _renderTexture;
            bool _animationToggle;
            bool _lowObject;
            bool _displayGameInfos;
        public:
            RaylibGraphical() = delete;
            RaylibGraphical(Map &map, GameplayEntitiesHolder& GEH);
            ~RaylibGraphical();

            void initWindow() override;
            void initCamera() override;

            bool run() override;

            void drawTiles() override;
            void displayTileInfo(tileCoordinates) override;
            void displayBroadcast() override;
            void drawPlayers() override;
            void drawGEHInfos() override;
            void displayGameInfos() override;
            void drawLowObject() override;
            void drawLowObjectTiles() override;
            void drawLowObjectPlayers() override;
            void handleLowObjectInputs() override;
            void displayLowObjectTileInfo(tileCoordinates) override;
            void displayLowObjectGameInfos() override;
            void fillGameInfos(std::map<std::string, int> &teamMap, std::array<int, 7> &resources);
            void drawTextureRect(RenderTexture2D&);
            void definePlayerAnimation(PlayerInfo &, std::pair<int, int> &);
            void updatePlayerAnimations(PlayerInfo &);
            void updateDyingPlayerAnimaions(PlayerInfo &);
            void drawPlayerInfo(PlayerInfo &);
            void drawEggInfo(Egg &);
            void drawParticles(tileCoordinates, raylib::Color);
            void highlightPlayerFOV(PlayerInfo &);
            bool getModelCollision(raylib::Model&, floatCoordinates, raylib::Ray, std::pair<int, int>, float height, Vector3, Vector3, float);
            // Maybe get this to interface by creating a zappy::Color object that could interpret more than a raylib color
            raylib::Color getTeamColor(std::string);
            void drawText(std::string str, int X, int Y, raylib::Color color);

            // TODO maybe add in interface
            void updateCamera();
    };
}
