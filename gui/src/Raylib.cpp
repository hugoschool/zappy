#include "Raylib.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "IEntity.hpp"
#include "Map.hpp"
#include "RaylibModelHolder.hpp"
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
#include <iostream>
#include <memory>
#include <cstdio>
#include <optional>
#include <raylib.h>
#include <raymath.h>
#include <utility>
#include <vector>
#include "Utils.hpp"

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map, GameplayEntitiesHolder &GEH): _map(map), _GEH(GEH),
    _window(), _camera(), _modelHolder(), _cameraTargetTarget({0, 0, 0}), _tickUntilCameraTarget(0), _particles(), _colorMap(), _playerAnimationsMap(), _shaderHolder(), _currentShader(0), _renderTexture()
{
    srand(time(NULL));
    initWindow();
    initCamera();
    _modelHolder.initModels();
    _renderTexture.Load(1000, 800);
    _shaderHolder.initShaders();
}

zappy::RaylibGraphical::~RaylibGraphical()
{
    _shaderHolder.unloadShaders();
    _renderTexture.Unload();
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

void zappy::RaylibGraphical::drawTextureRect(RenderTexture2D &text)
{
    BeginTextureMode(text);
    _window.ClearBackground(raylib::Color::RayWhite());
    BeginMode3D(_camera);

    drawTiles();
    drawPlayers();

    EndMode3D();
    EndTextureMode();
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
    if (IsKeyPressed(KEY_P))
        _currentShader++;

    //------//
    //-Draw-//
    //------//
    drawTextureRect(_renderTexture);
    _window.BeginDrawing();
    _window.ClearBackground(raylib::Color::RayWhite());
    std::optional<raylib::Shader> &shader = _shaderHolder.getShader(_currentShader);
    if (shader.has_value())
        BeginShaderMode(shader.value());
    DrawTextureRec(_renderTexture.texture, (Rectangle){ 0, 0, static_cast<float>(_renderTexture.texture.width), static_cast<float>(-_renderTexture.texture.height) }, (Vector2){ 0, 0 }, WHITE);
    if (shader.has_value())
        EndShaderMode();
    for (auto &tile: _map.getTiles()) {
        if (tile.second.isSelected()) {
            displayTileInfo(tile.second.getCoords());
        }
    }
    drawGEHInfos();
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

bool zappy::RaylibGraphical::getModelCollision(raylib::Model &model, floatCoordinates pos, raylib::Ray ray, std::pair<int, int> mapDimensions, float height, Vector3 scale, Vector3 rotation, float angle)
{
    for (int i = 0; i < model.meshCount; i++) {
        // TODO ajouter la matrice de rotation
        raylib::Matrix matT = MatrixTranslate(pos.first - mapDimensions.first / 2.0 + 0.5, height, pos.second - mapDimensions.second / 2.0 + 0.5);
        raylib::Matrix matS = MatrixScale(scale.x, scale.y, scale.z);
        raylib::Matrix matR = MatrixRotate(rotation, angle);
        raylib::Matrix mat = MatrixMultiply(MatrixMultiply(matS, matR), matT); // fonctionne un peu mais pas trop
        RayCollision collision = GetRayCollisionMesh(ray, model.meshes[i], mat);
        if (collision.hit == true) {
            return true;
        }
    }
    return false;
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

        for (auto &player: _GEH.getPlayers()) {
            const floatCoordinates pos = player.second.getDisplayCoords();
            player.second.setSelected(getModelCollision(_modelHolder.getPlayerModel(), pos, ray, mapDimensions, 0.1, Vector3(0.1, 0.1, 0.1), Vector3(0, 0.1, 0), static_cast<float>(zappy::Utils::getOrientation(player.second.getOrientation()))));
        }
        for (auto &egg: _GEH.getEggs()) {
            const floatCoordinates pos = egg.second.getDisplayCoords();
            egg.second.setSelected(getModelCollision(_modelHolder.getEggModel(), pos, ray, mapDimensions, 0.15, Vector3(0.1, 0.1, 0.1), Vector3(0, 0, 0), 0));
        }
        for (int y = 0; y < mapDimensions.second; y++) {
            for (int x = 0; x < mapDimensions.first; x++) {
                zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));

                // Reset selected tiles
                tile.setSelectedState(false);
                const Vector3 &tileDisplayCoords = tile.getDisplayCoordinates();
                RayCollision collision = GetRayCollisionBox(ray, {{tileDisplayCoords.x - 1.0f/2.0f, tileDisplayCoords.y - 0.1f/2.0f, tileDisplayCoords.z - 1.0f/2.0f}, {tileDisplayCoords.x + 1.0f/2.0f, tileDisplayCoords.y + 0.1f/2.0f, tileDisplayCoords.z + 1.0f/2.0f}});
                
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

void zappy::RaylibGraphical::drawParticles(PlayerInfo &info)
{
    RaylibParticles &particles = _particles.at(info.getDisplayCoords());
    particles.update();
    std::array<std::optional<ParticlesData>, MAX_PARTICLES> dataArray = particles.getDataArray();
    int head = particles.getHead();
    raylib::Color color = getTeamColor(info);

    for (int i = particles.getTail(); i != head; i = (i + 1) % MAX_PARTICLES) {
        if (dataArray.at(i).has_value()) {
            ParticlesData data = dataArray.at(i).value();
            color.SetA(data._color.GetA());
            DrawSphere(data._position, data._radius, color);
        }
    }
}

void zappy::RaylibGraphical::displayTileInfo(zappy::tileCoordinates coords)
{
    Tile &tile = _map.getTile(coords);
    raylib::Rectangle rect(10, 10, 200, 170);
    std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
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
    const int width = _window.GetRenderWidth();
    const int height = _window.GetRenderHeight();
    raylib::Rectangle rect(width - 325, height - 200, 300, 180);

    rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Broadcast", width - 225, height - 190, raylib::Color::Black());
    while (_GEH.getBroadcast().size() > 0) {
        std::pair<int, std::string> message = _GEH.popMessage();
        // TODO get player name by id instead of just id
        std::string messageToDisplay = std::to_string(message.first) + ": " + message.second;
        _broadcastToDisplay.push_back(messageToDisplay);
    }
    while (_broadcastToDisplay.size() > 6) {
        _broadcastToDisplay.erase(_broadcastToDisplay.begin());
    }
    int pos = height - 175;
    for (std::string msg: _broadcastToDisplay) {
        drawText(msg, width - 315, pos, raylib::Color::Black());
        pos += 20;
    }
}

void zappy::RaylibGraphical::drawPlayers()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();
    for (auto &player: _GEH.getPlayers()) {
        player.second.updateDisplayPos();
        const floatCoordinates playerCoords = player.second.getDisplayCoords();
        Vector3 rotationAxis(0, 0.1, 0);
        float rotationAngle = static_cast<float>(zappy::Utils::getOrientation(player.second.getOrientation())) + 90.0f;

        Vector3 playerPosition(playerCoords.first - mapDimensions.first / 2.0f + 0.5, 0.1, playerCoords.second - mapDimensions.second / 2.0f + 0.5);
        Vector3 playerScale(0.1, 0.1, 0.1);

        _modelHolder.getPlayerModel().Draw(playerPosition, rotationAxis, rotationAngle, playerScale);

        if (player.second.isIncantating()) {
            try {
                _particles.at(playerCoords);
            } catch (std::out_of_range) {
                _particles.insert({playerCoords, RaylibParticles(playerCoords, mapDimensions)});
            }
            drawParticles(player.second);
        }
        if (player.second.getSelected()) {
            // Highlight the player skeleton
            _modelHolder.getPlayerModel().DrawWires(playerPosition, rotationAxis, rotationAngle, playerScale);

            highlightPlayerFOV(player.second);
        }
        updatePlayerAnimations(player.second);
    }
    for (auto &egg: _GEH.getEggs()) {
        const floatCoordinates eggCoords = egg.second.getDisplayCoords();
        _modelHolder.getEggModel().Draw(Vector3(eggCoords.first - mapDimensions.first / 2.0f + 0.5, 0.15, eggCoords.second - mapDimensions.second / 2.0f + 0.8), 0.1f);
    }
    return;
}

void zappy::RaylibGraphical::updatePlayerAnimations(PlayerInfo &info)
{
    const int playerID = info.getId();

    try {
        _playerAnimationsMap.at(playerID);
    } catch (std::out_of_range) {
        _playerAnimationsMap.insert({playerID, std::pair(ROBOT_IDLE, 0)});
    }
    std::pair<int, int> &animIndexAndFrame = _playerAnimationsMap.at(playerID);
    if (info.isMoving()) {
        animIndexAndFrame.first = ROBOT_RUN;
    } else if (info.isIncantating()) {
        animIndexAndFrame.first = ROBOT_INCANTATION;
    } else {
        animIndexAndFrame.first = ROBOT_IDLE;
    }
    _modelHolder.getPlayerModel().UpdateAnimation(_modelHolder.getPlayerAnimations()[animIndexAndFrame.first], animIndexAndFrame.second);
    animIndexAndFrame.second++;
}

void zappy::RaylibGraphical::drawPlayerInfo(PlayerInfo &info)
{
    const int height = _window.GetRenderHeight();
    raylib::Rectangle rect(10, height - 200, 250, 90);
    const tileCoordinates coords = info.getCoords();
    rect.Draw(Fade(getTeamColor(info), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Player " + std::to_string(info.getId()) + " Infos", 15, height - 190, raylib::Color::Black());
    drawText("Part of " + info.getTeamName() + " team", 15, height - 170, raylib::Color::Black());
    drawText("Level " + std::to_string(info.getLevel()), 15, height - 150, raylib::Color::Black());
    drawText("On tile " + std::to_string(coords.first) + " " + std::to_string(coords.second), 15, height - 130, raylib::Color::Black());

    auto inventory = info.getInventory();
    raylib::Rectangle otherRect(260, height - 200, 185, 180);
    otherRect.Draw(Fade(getTeamColor(info), 0.5f));
    otherRect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Player Inventory", 265, height - 190, raylib::Color::Black());
    drawText(std::to_string(inventory.at("food")) + " Food", 265, height - 170, raylib::Color::Brown());
    drawText(std::to_string(inventory.at("Linemate")) + " Linemate", 265, height - 150, raylib::Color::Yellow());
    drawText(std::to_string(inventory.at("Deraumere")) + " Deraumere", 265, height - 130, raylib::Color::Green());
    drawText(std::to_string(inventory.at("Sibur")) + " Sibur", 265, height - 110, raylib::Color::Red());
    drawText(std::to_string(inventory.at("Mendiane")) + " Mendiane", 265, height - 90, raylib::Color::SkyBlue());
    drawText(std::to_string(inventory.at("Phiras")) + " Phiras", 265, height - 70, raylib::Color::DarkBlue());
    drawText(std::to_string(inventory.at("Thystame")) + " Thystame", 265, height - 50,raylib::Color::Purple());
}

void zappy::RaylibGraphical::drawEggInfo(Egg &egg)
{
    const int height = _window.GetRenderHeight();
    raylib::Rectangle rect(10, height - 110, 250, 90);
    const tileCoordinates coords = egg.getCoords();
    if (egg.getTeamName() == "")
        rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    else
        rect.Draw(Fade(getTeamColor(egg), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Egg " + std::to_string(egg.getId()) + " Infos", 15, height - 100, raylib::Color::Black());
    if (egg.getTeamName() == "") {
        drawText("Not part of a team yet", 15, height - 80, raylib::Color::Black());
    } else {
        drawText("Part of " + egg.getTeamName() + " team", 15, height - 80, raylib::Color::Black());
    }
    drawText("On tile " + std::to_string(coords.first) + " " + std::to_string(coords.second), 15, height - 60, raylib::Color::Black());
}

void zappy::RaylibGraphical::drawGEHInfos()
{
    for (auto &player: _GEH.getPlayers()) {
        if (player.second.getSelected()) {
            drawPlayerInfo(player.second);
        }
    }
    for (auto &egg: _GEH.getEggs()) {
        if (egg.second.getSelected()) {
            drawEggInfo(egg.second);
        }
    }
}

void zappy::RaylibGraphical::highlightPlayerFOV(PlayerInfo &info)
{
    int orientation = zappy::Utils::getFOVOrientation(info.getOrientation());
    int level = info.getLevel();
    const tileCoordinates coords = info.getCoords();
    const std::pair<int, int> mapDimensions = _map.getDimensions();
    highlight_values_t vals = {0, 0, 0, 0};

    switch (orientation) {
        case 0:
            vals = {-1, 0, 0, 1};
            break;
        case 90:
            vals = {0, -1, 1, 0};
            break;
        case 180:
            vals = {1, 0, 0, 1};
            break;
        case 270:
            vals = {0, 1, 1, 0};
            break;
        default:
            break;
    }
    for (int i = 0; i < level; i++) {
        Tile tile = _map.getTile(zappy::Utils::handleTileOverflow(tileCoordinates(coords.first + vals.fx * (i + 1), coords.second + vals.fy * (i + 1)), mapDimensions));
        DrawCubeWires(tile.getDisplayCoordinates(), 1.0f, 0.1f, 1.0f, getTeamColor(info));
        for (int j = 0; j < i + 1; j++) {
            tile = _map.getTile(zappy::Utils::handleTileOverflow(tileCoordinates((coords.first + vals.fx * (i + 1)) - (vals.sx * (j + 1)) , (coords.second + vals.fy * (i + 1)) - (vals.sy * (j + 1))), mapDimensions));
            DrawCubeWires(tile.getDisplayCoordinates(), 1.0f, 0.1f, 1.0f, getTeamColor(info));
            tile = _map.getTile(zappy::Utils::handleTileOverflow(tileCoordinates((coords.first + vals.fx * (i + 1)) + (vals.sx * (j + 1)) , (coords.second + vals.fy * (i + 1)) + (vals.sy * (j + 1))), mapDimensions));
            DrawCubeWires(tile.getDisplayCoordinates(), 1.0f, 0.1f, 1.0f, getTeamColor(info));
        }
    }
}

raylib::Color zappy::RaylibGraphical::getTeamColor(IPlayer &info)
{
    std::string name = info.getTeamName();

    if (name == "") {
        return raylib::Color::Black();
    }
    raylib::Color color(rand() % 255, rand() % 255, rand() % 255);

    try {
        color = _colorMap.at(name);
    } catch (std::out_of_range) {
        _colorMap.insert({name, color});
    }
    return color;
}
