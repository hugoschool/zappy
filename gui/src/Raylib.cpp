#include "Raylib.hpp"
#include "GameplatEntitiesHolder.hpp"
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

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map, GameplayEntitiesHolder &GEH): _map(map), _GEH(GEH),
    _window(), _camera(), _modelHolder(), _cameraTargetTarget({0, 0, 0}), _tickUntilCameraTarget(0), _particles()
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
    drawPlayers();

    EndMode3D();
    for (auto tile: _map.getTiles()) {
        if (tile.second.isSelected()) {
            displayTileInfo(tile.second.getCoords());
        }
    }
    displayBroadcast();
    _window.DrawFPS(920, 10);

    _window.EndDrawing();
    return exit;
}

void zappy::RaylibGraphical::drawTiles()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));

            DrawCube(tile.getDisplayCoordinates(), 1.0f, 0.1f, 1.0f, (tile.isSelected()) ? raylib::Color::Red() : raylib::Color::Green());
            DrawCubeWires(tile.getDisplayCoordinates(), 1.0f, 0.1f, 1.0f, raylib::Color::Black());

            std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
            for (auto &entity: entities) {
                entity->draw(_modelHolder, mapDimensions);
            }
        }
    }
}

void zappy::RaylibGraphical::drawText(std::string str, int X, int Y, raylib::Color color)
{
    raylib::DrawText(str, X, Y, 20, color);
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
    raylib::Rectangle rect(10, 10, 200, 170);
    std::vector<std::shared_ptr<IEntity>> entities = tile.getEntities();
    if (entities.size() == 0)
        return;
    std::array<std::string, 7> resources;

    rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Tile " + std::to_string(coords.first) + " " + std::to_string(coords.second) + " infos", 15, 15, raylib::Color::Black());
    resources[0] = std::to_string(entities[0]->getAmount());
    resources[1] = std::to_string(entities[1]->getAmount());
    resources[2] = std::to_string(entities[2]->getAmount());
    resources[3] = std::to_string(entities[3]->getAmount());
    resources[4] = std::to_string(entities[4]->getAmount());
    resources[5] = std::to_string(entities[5]->getAmount());
    resources[6] = std::to_string(entities[6]->getAmount());
    drawText(resources[0] + " Food", 20, 35, raylib::Color::Brown());
    drawText(resources[1] + " Linemate", 20, 55, raylib::Color::Yellow());
    drawText(resources[2] + " Deraumere", 20, 75, raylib::Color::Green());
    drawText(resources[3] + " Sibur", 20, 95, raylib::Color::Red());
    drawText(resources[4] + " Mendiane", 20, 115, raylib::Color::SkyBlue());
    drawText(resources[5] + " Phiras", 20, 135, raylib::Color::DarkBlue());
    drawText(resources[6] + " Thystame", 20, 155,raylib::Color::Purple());
}

void zappy::RaylibGraphical::displayBroadcast()
{
    raylib::Rectangle rect(675, 600, 300, 180);

    rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Broadcast", 785, 610, raylib::Color::Black());
    while (_GEH.getBroadcast().size() > 0) {
        std::pair<int, std::string> message = _GEH.popMessage();
        // TODO get player name by id instead of just id
        std::string messageToDisplay = std::to_string(message.first) + ": " + message.second;
        _broadcastToDisplay.push_back(messageToDisplay);
    }
    while (_broadcastToDisplay.size() > 6) {
        _broadcastToDisplay.erase(_broadcastToDisplay.begin());
    }
    int pos = 635;
    for (std::string msg: _broadcastToDisplay) {
        drawText(msg, 685, pos, raylib::Color::Black());
        pos += 20;
    }
}

void zappy::RaylibGraphical::drawPlayers()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();
    for (auto player: _GEH.getPlayers()) {
        PlayerInfo &info = player.second;
        const tileCoordinates playerCoords = info.getCoords();
        if (info.isEgg()) {
            _modelHolder.getEggModel().Draw(Vector3(playerCoords.first - mapDimensions.first / 2.0f + 0.5, 0.15, playerCoords.second - mapDimensions.second / 2.0f + 0.8), 0.1f);
        } else {
            Vector3 rotationAxis(playerCoords.first - mapDimensions.first / 2.0f + 0.5, 0.5, playerCoords.second - mapDimensions.second / 2.0f + 0.5);
            float rotationAngle = static_cast<float>(info.getOrientation());
            _modelHolder.getFoodModel().Draw(Vector3(playerCoords.first - mapDimensions.first / 2.0f + 0.5, 0.1, playerCoords.second - mapDimensions.second / 2.0f + 0.5), rotationAxis, rotationAngle, Vector3(2.5, 2.5, 2.5));
        }

        if (info.isIncantating()) {
            try {
                _particles.at(playerCoords);
            } catch (std::out_of_range) {
                _particles.insert({playerCoords, RaylibParticles(playerCoords, mapDimensions)});
            }
            drawParticles(playerCoords);
        }
    }
    return;
}
