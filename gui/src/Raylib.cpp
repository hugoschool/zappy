#include "Raylib.hpp"
#include "IEntity.hpp"
#include "Map.hpp"
#include "RaylibParticles.hpp"
#include "Tile.hpp"
#include "entities/Materials.hpp"
#include <Camera3D.hpp>
#include <Color.hpp>
#include <Functions.hpp>
#include <Keyboard.hpp>
#include <Material.hpp>
#include <Mouse.hpp>
#include <Vector3.hpp>
#include <memory>
#include <cstdio>
#include <optional>
#include <raylib.h>
#include <utility>
#include <vector>

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map): _map(map), _window(),
    _camera(), _modelHolder(), _cameraTargetTarget({0, 0, 0}), _tickUntilCameraTarget(0), _particles()
{
    initWindow();
    initCamera();
    _modelHolder.initModels();
}

zappy::RaylibGraphical::~RaylibGraphical()
{
    _modelHolder.unloadModels();
    _window.Close();
}

void zappy::RaylibGraphical::initWindow()
{
    _window.Init(1000, 800, "zappy");
    _window.SetTargetFPS(60);
}

void zappy::RaylibGraphical::initCamera()
{
    _camera.SetPosition({10.0, 10.0, 10.0}); // Camera position
    _camera.SetTarget({0, 0, 0}); // Camera looking at point
    _camera.SetUp({ 0.0f, 1.0f, 0.0f }); // Camera up vector (rotation towards target)
    _camera.SetFovy(45); // Camera field-of-view Y
    _camera.SetProjection(CAMERA_PERSPECTIVE);
}

bool zappy::RaylibGraphical::run()
{
    bool exit = false;

    //-------------//
    //-Move-Camera-//
    //-------------//
    updateCamera();

    if (_window.ShouldClose()) {
        exit = true;
    }

    //------//
    //-Draw-//
    //------//
    _window.BeginDrawing();
    _window.ClearBackground(raylib::Color::RayWhite());

    BeginMode3D(_camera);

    drawTiles();

    EndMode3D();
    for (auto tile: _map.getTiles()) {
        if (tile.second.isSelected()) {
            displayTileInfo(tile.second.getCoords());
        }
    }
    _window.DrawFPS();

    _window.EndDrawing();
    return exit;
}

void zappy::RaylibGraphical::drawTiles()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));
            const tileCoordinates tileCoords = tile.getCoords();

            DrawCube(tile.getDisplayCoordinates(), 1.0f, 0.1f, 1.0f, (tile.isSelected()) ? raylib::Color::Red() : raylib::Color::Green());
            DrawCubeWires(tile.getDisplayCoordinates(), 1.0f, 0.1f, 1.0f, raylib::Color::Black());
    
            std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
            for (auto &entity: entities) {
                entity->draw(_modelHolder, mapDimensions);
            }
            if (tile.isIncantating()) {
                try {
                    _particles.at(tileCoords);
                } catch (std::out_of_range) {
                    _particles.insert({tileCoords, RaylibParticles(tileCoords, mapDimensions)});
                }
                drawParticles(tileCoords);
            }
        }
    }
}

void zappy::RaylibGraphical::drawText(std::string str, int X, int Y)
{
    raylib::DrawText(str, X, Y, 20, raylib::Color::Black());
}

void zappy::RaylibGraphical::updateCamera()
{
    // Camera angle moveable while holding the click.
    if (raylib::Mouse::IsButtonDown(MOUSE_BUTTON_RIGHT)) {
        _camera.Update(CAMERA_THIRD_PERSON);
        // TODO save the cursor pos to put it back at the same place
        // DisableCursor();
    }
    if (raylib::Mouse::IsButtonUp(MOUSE_BUTTON_RIGHT)) {
        _camera.Update(CAMERA_CUSTOM);
        // TODO La suite
        // EnableCursor();
    }
    // Handle scrolling
    float scroll = raylib::Mouse::GetWheelMove();
    if (scroll != 0) {
        _camera.Update(CAMERA_THIRD_PERSON);
    } else {
        _camera.Update(CAMERA_CUSTOM);
    }


    // Selecte a tile
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Ray ray = GetScreenToWorldRay(GetMousePosition(), _camera);
        
        zappy::Tile *closestTileHit;
        std::optional<float> closestDistance = std::nullopt;

        // Check collision between ray and box
        const std::pair<int, int> mapDimensions = _map.getDimensions();

        for (int y = 0; y < mapDimensions.second; y++) {
            for (int x = 0; x < mapDimensions.first; x++) {
                zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));

                // Reset selected tiles
                tile.setSelectedState(false);

                RayCollision collision = GetRayCollisionBox(ray, {{tile.getDisplayCoordinates().x - 1.0f/2.0f, tile.getDisplayCoordinates().y - 0.1f/2.0f, tile.getDisplayCoordinates().z - 1.0f/2.0f}, {tile.getDisplayCoordinates().x + 1.0f/2.0f, tile.getDisplayCoordinates().y + 0.1f/2.0f, tile.getDisplayCoordinates().z + 1.0f/2.0f}});
                
                if (collision.hit == true) {
                    if (closestDistance.has_value() == false || collision.distance < closestDistance) {
                        closestDistance = collision.distance;
                        closestTileHit = &tile;
                    }
                }
            }
        }
        // Set new camera target target
        if (closestDistance.has_value() == true) {
            closestTileHit->setSelectedState(true);
            _cameraTargetTarget = closestTileHit->getDisplayCoordinates();
            _tickUntilCameraTarget = TICK_TO_CAMERA_TARGET;
        } else {
            _cameraTargetTarget = {0, 0, 0};
            _tickUntilCameraTarget = TICK_TO_CAMERA_TARGET;
        }
    }

    // Update the camera target
    if (_tickUntilCameraTarget == 1) {
        _camera.SetTarget(_cameraTargetTarget);
        _tickUntilCameraTarget = 0;
    } else if (_tickUntilCameraTarget > 1) {
        Vector3 travelVector = {_cameraTargetTarget.x - _camera.GetTarget().x, _cameraTargetTarget.y - _camera.GetTarget().y, _cameraTargetTarget.z - _camera.GetTarget().z};
        _camera.SetTarget({_camera.GetTarget().x + (travelVector.x / _tickUntilCameraTarget), _camera.GetTarget().y + (travelVector.y / _tickUntilCameraTarget), _camera.GetTarget().z + (travelVector.z / _tickUntilCameraTarget)});
        _tickUntilCameraTarget -= 1;
    }
}

void zappy::RaylibGraphical::drawParticles(zappy::tileCoordinates coords)
{
    RaylibParticles &particles = _particles.at(coords);
    particles.update();
    std::array<std::optional<ParticlesData>, MAX_PARTICLES> dataArray = particles.getDataArray();
    int head = particles.getHead();

    for (int i = particles.getTail(); i != head; i = (i + 1) % MAX_PARTICLES) {
        if (dataArray.at(i).has_value()) {
            ParticlesData data = dataArray.at(i).value();
            DrawSphere(data._position, data._radius, data._color);
        }
    }
}

void zappy::RaylibGraphical::displayTileInfo(zappy::tileCoordinates coords)
{
    Tile tile = _map.getTile(coords);
    raylib::Rectangle rect(10, 30, 200, 170);
    std::vector<std::shared_ptr<IEntity>> entities = tile.getEntities();
    if (entities.size() == 0)
        return;
    std::array<std::string, 7> resources;

    rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    resources[0] = std::to_string(entities[0]->getAmount());
    resources[1] = std::to_string(entities[1]->getAmount());
    resources[2] = std::to_string(entities[2]->getAmount());
    resources[3] = std::to_string(entities[3]->getAmount());
    resources[4] = std::to_string(entities[4]->getAmount());
    resources[5] = std::to_string(entities[5]->getAmount());
    resources[6] = std::to_string(entities[6]->getAmount());
    drawText(resources[0] + " Food", 15, 40);
    drawText(resources[1] + " Linemate", 15, 60);
    drawText(resources[2] + " Deraumere", 15, 80);
    drawText(resources[3] + " Sibur", 15, 100);
    drawText(resources[4] + " Mendiane", 15, 120);
    drawText(resources[5] + " Phiras", 15, 140);
    drawText(resources[6] + " Thystame", 15, 160);
}
