#include "Raylib.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "IEntity.hpp"
#include "Map.hpp"
#include "RaylibModelHolder.hpp"
#include "RaylibParticles.hpp"
#include "Tile.hpp"
#include <Camera3D.hpp>
#include <Color.hpp>
#include <Functions.hpp>
#include <Keyboard.hpp>
#include <Material.hpp>
#include <Mouse.hpp>
#include <Texture.hpp>
#include <Vector3.hpp>
#include <cstddef>
#include <memory>
#include <cstdio>
#include <optional>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <utility>
#include <vector>
#include "Utils.hpp"
#include "entities/Food.hpp"
#include "entities/Materials.hpp"

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map, GameplayEntitiesHolder &GEH): _map(map), _GEH(GEH),
    _window(), _camera(), _modelHolder(), _cameraTargetTarget({0, 0, 0}), _tickUntilCameraTarget(0), _particles(), _colorMap(), _playerAnimationsMap(), _dyingPlayerAnimationsMap(), _shaderHolder(), _currentShader(0), _renderTexture(), _animationToggle(false), _lowObject(false), _displayGameInfos(false)
{
    srand(time(NULL));
    initWindow();
    initCamera();
    InitAudioDevice();
    _modelHolder.initModels();
    _renderTexture.Load(1200, 1000);
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
    _window.Init(1200, 1000, "zappy");
    _window.SetTargetFPS(180);
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
    int scroll = _modelHolder.updateBackgroundScroll();
    raylib::Texture2D& bkg = _modelHolder.getBackground();
    bkg.Draw(Vector2(scroll, 0), 0.0f, 2.0f, raylib::Color::White());
    bkg.Draw(Vector2(-(bkg.width * 2) + scroll, 0), 0.0f, 2.0f, raylib::Color::White());
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

    if (_window.ShouldClose()) {
        exit = true;
    }
    if (raylib::Keyboard::IsKeyPressed(KEY_L)) {
        _lowObject = !_lowObject;
    }

//------//
//-Draw-//
//------//
    if (!_lowObject) {
        updateCamera();
        if (raylib::Keyboard::IsKeyPressed(KEY_P))
            _currentShader++;
        if (raylib::Keyboard::IsKeyPressed(KEY_O))
            _animationToggle = !_animationToggle;
        if (raylib::Keyboard::IsKeyPressed(KEY_I))
            _displayGameInfos = !_displayGameInfos;
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
        displayGameInfos();
        _window.DrawFPS(1120, 10);

        _window.EndDrawing();
    } else {
        _window.BeginDrawing();
        _window.ClearBackground(raylib::Color::Black());
        drawLowObject();
        _window.EndDrawing();
    }
    return exit;
}

void zappy::RaylibGraphical::drawTiles()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));

            raylib::Vector3 displayCoordinates = convertVector3D(tile.getDisplayCoordinates());

            _modelHolder.getGrassModel().Draw(displayCoordinates, 1, tile.isSelected() ? raylib::Color::Blue() : raylib::Color::White());
            DrawCubeWires(displayCoordinates, 1.0f, 0.1f, 1.0f, raylib::Color::Black());

            std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
            for (auto &entity: entities) {
                drawEntity(entity, mapDimensions);
            }
        }
    }
}

void zappy::RaylibGraphical::drawEntity(std::shared_ptr<zappy::IEntity> &entity, const std::pair<int, int> &mapDimensions)
{
    const tileCoordinates coords = entity->getCoords();
    const int amount = entity->getAmount();
    if (amount == 0)
        return;
    Food *food = dynamic_cast<Food*>(entity.get());
    zappy::Material *mat = dynamic_cast<zappy::Material*>(entity.get());

    if (food != nullptr) {
        float heightVal = 0.05;
        for (int i = 0; i < (amount > 20 ? 20 : amount); i++) {
            _modelHolder.getFoodModel().Draw(Vector3(coords.first - (mapDimensions.first / 2.0f) - 0.2 + 0.5f, heightVal, coords.second - (mapDimensions.second / 2.0f) + 0.5f), 1.0f);
            heightVal += 0.05;
        }
    }
    if (mat != nullptr) {
        const std::tuple color = mat->getMaterialColor();
        const std::pair<float, float> position = mat->getMaterialPosition(mapDimensions);
        _modelHolder.getMaterialModel().Draw(Vector3(position.first, 0.05, position.second), 0.5f, raylib::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color)));
    }
}

void zappy::RaylibGraphical::drawLowObjectEntity(std::shared_ptr<IEntity> &entity, const std::pair<int, int>& mapDimensions)
{
    const tileCoordinates coords = entity->getCoords();
    const int amount = entity->getAmount();
    Food *food = dynamic_cast<Food*>(entity.get());
    zappy::Material *mat = dynamic_cast<zappy::Material*>(entity.get());

    if (food != nullptr) {
        std::string str = std::to_string(amount);
        raylib::DrawText(str.c_str(), (coords.first * 20 + 1) / (mapDimensions.first / 42.0f), (coords.second * 20 + 1) / (mapDimensions.second / 42.0f), 10, raylib::Color::Brown());
    }
    if (mat != nullptr) {
        if (mapDimensions.first > 20 || mapDimensions.second > 20)
            return;
        std::string str = std::to_string(amount);
        const int posYAdd = (static_cast<int>(mat->getMaterialType()) + 2) * (20 / 7);
        const std::tuple color = mat->getMaterialColor();
        raylib::DrawText(str.c_str(), (coords.first * 20 + 1) / (mapDimensions.first / 42.0f), (coords.second * 20 + posYAdd) / (mapDimensions.second / 42.0f), 3 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), raylib::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color)));
    }
}

void zappy::RaylibGraphical::drawText(std::string str, int X, int Y, raylib::Color color)
{
    raylib::DrawText(str, X, Y, 20, color);
}

bool zappy::RaylibGraphical::getModelCollision(raylib::Model &model, floatCoordinates pos, raylib::Ray ray, std::pair<int, int> mapDimensions, float height, Vector3 scale, Vector3 rotation, float angle)
{
    for (int i = 0; i < model.meshCount; i++) {
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
            egg.second.setSelected(getModelCollision(_modelHolder.getEggModel(), pos, ray, mapDimensions, 0.15, Vector3(0.25, 0.25, 0.25), Vector3(0, 0, 0), 0));
        }
        for (int y = 0; y < mapDimensions.second; y++) {
            for (int x = 0; x < mapDimensions.first; x++) {
                zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));

                // Reset selected tiles
                tile.setSelectedState(false);
                const raylib::Vector3 &tileDisplayCoords = convertVector3D(tile.getDisplayCoordinates());
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
            _cameraTargetTarget = convertVector3D(closestTileHit->getDisplayCoordinates());
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

std::map<std::string, std::pair<int, int>> zappy::RaylibGraphical::fillGameInfos(std::map<std::string, int> &teamMap, std::array<int, 7> &resources)
{
    std::map<std::string, std::pair<int, int>> highLevelMap;

    const std::pair<int, int> mapDimensions = _map.getDimensions();
    for (auto &player: _GEH.getPlayers()) {
        try {
            teamMap.at(player.second.getTeamName()) += 1;
        } catch (std::out_of_range) {
            teamMap.insert({player.second.getTeamName(), 1});
        }
        try {
            highLevelMap.at(player.second.getTeamName());
        } catch (std::out_of_range) {
            highLevelMap.insert({player.second.getTeamName(), std::pair(0, 0)});
        }
        const int playerLevel = player.second.getLevel();
        for (auto &pair: highLevelMap) {
            if (playerLevel == pair.second.first)
                pair.second.second++;
            if (playerLevel > pair.second.first) {
                pair.second.first = playerLevel;
                pair.second.second = 1;
            }
        }
    }
    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            Tile &tile = _map.getTile(tileCoordinates(x, y));

            // Cannot use entitiesToResources here as it adds to the current resources
            std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
            if (entities.size() != 7)
                continue;
            for (unsigned int i = 0; i < 7; i++) {
                resources[i] += entities[i]->getAmount();
            }
        }
    }
    return highLevelMap;
}

void zappy::RaylibGraphical::displayGameInfos()
{
    if (!_displayGameInfos)
        return;
    std::map<std::string, int> teamMap;
    std::array<int, 7> resources;
    resources.fill(0);
    std::map<std::string, std::pair<int, int>> highLevelMap = fillGameInfos(teamMap, resources);
    const int width = _window.GetRenderWidth();
    const int height = _window.GetRenderHeight();
    raylib::Rectangle rect(width - 325, height - 600, 300, 400);

    rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Game Infos", width - 225, height - 590, raylib::Color::Black());
    int pos = height - 570;

    for (auto &team: teamMap) {
        drawText("Team " + team.first + " : " + std::to_string(team.second) + " players", width - 320, pos, getTeamColor(team.first));
        auto &correspondingTeam = highLevelMap.at(team.first);
        drawText("Highest level " + std::to_string(correspondingTeam.first) + " : " + std::to_string(correspondingTeam.second) + " players", width - 320, pos + 20, getTeamColor(team.first));
        pos += 40;
    }

    drawMaterials(resources, width - 320, pos);
}

void zappy::RaylibGraphical::displayLowObjectGameInfos()
{
    std::map<std::string, int> teamMap;
    std::array<int, 7> resources;
    resources.fill(0);
    std::map<std::string, std::pair<int, int>> highLevelMap = fillGameInfos(teamMap, resources);
    const int width = _window.GetRenderWidth();
    drawText("Game Infos", width - 335, 20, raylib::Color::White());
    int pos = 40;
    for (auto &team: teamMap) {
        drawText("Team " + team.first + " : " + std::to_string(team.second) + " players", width - 335, pos, getTeamColor(team.first));
        auto &correspondingTeam = highLevelMap.at(team.first);
        drawText("Highest level " + std::to_string(correspondingTeam.first) + " : " + std::to_string(correspondingTeam.second) + " players", width - 335, pos + 20, getTeamColor(team.first));
        pos += 40;
    }
    drawMaterials(resources, width - 335, pos);
}

void zappy::RaylibGraphical::handleLowObjectInputs()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    if (raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
        const Vector2 mouseCoords = raylib::Mouse::GetPosition();
        for (int y = 0; y < mapDimensions.second; y++) {
            for (int x = 0; x < mapDimensions.first; x++) {
                Tile &tile = _map.getTile(tileCoordinates(x, y));
                tile.setSelectedState(false);
                const tileCoordinates tileCoords = tile.getCoords();
                raylib::Rectangle rect((tileCoords.first * 20) / (mapDimensions.first / 42.0f), (tileCoords.second * 20) / (mapDimensions.second / 42.0f), 20 / (mapDimensions.first / 42.0f), 20 / (mapDimensions.second / 42.0f));

                if (rect.CheckCollision(mouseCoords)) {
                    tile.setSelectedState(true);
                }
            }
        }
    }
}

void zappy::RaylibGraphical::drawLowObject()
{
    _window.DrawFPS(1120, 10);
    handleLowObjectInputs();
    displayLowObjectGameInfos();
    drawLowObjectTiles();
    drawLowObjectPlayers();
    displayLowObjectBroadcast();
}

void zappy::RaylibGraphical::drawLowObjectTiles()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));
            raylib::Rectangle rect((x * 20) / (mapDimensions.first / 42.0f) , (y * 20) / (mapDimensions.second / 42.0f) , (20) / (mapDimensions.first / 42.0f), (20) / (mapDimensions.second / 42.0f));

            rect.DrawLines(raylib::Color::White());
            std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
            for (auto &entity: entities) {
                drawLowObjectEntity(entity, mapDimensions);
            }
            if (tile.isSelected()) {
                displayLowObjectTileInfo(tile.getCoords());
            }
        }
    }
}

void zappy::RaylibGraphical::drawLowObjectPlayers()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (auto &player: _GEH.getPlayers()) {
        player.second.updateDisplayPos();
        const tileCoordinates coords = player.second.getCoords();
        DrawCircle((coords.first * 20 + 10) / (mapDimensions.first / 42.0f), (coords.second * 20 + 10) / (mapDimensions.second / 42.0f), 7 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), getTeamColor(player.second.getTeamName()));
        if (player.second.isIncantating()) {
            DrawCircleLines((coords.first * 20 + 10) / (mapDimensions.first / 42.0f), (coords.second * 20 + 10) / (mapDimensions.second / 42.0f), 13 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), getTeamColor(player.second.getTeamName()));
        }
        switch (player.second.getOrientation()) {
            case 1:
                DrawCircle((coords.first * 20 + 10) / (mapDimensions.first / 42.0f), (coords.second * 20 + 5) / (mapDimensions.second / 42.0f), 3 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), raylib::Color::SkyBlue());
                break;
            case 2:
                DrawCircle((coords.first * 20 + 15) / (mapDimensions.first / 42.0f), (coords.second * 20 + 10) / (mapDimensions.second / 42.0f), 3 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), raylib::Color::SkyBlue());
                break;
            case 3:
                DrawCircle((coords.first * 20 + 10) / (mapDimensions.first / 42.0f), (coords.second * 20 + 15) / (mapDimensions.second / 42.0f), 3 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), raylib::Color::SkyBlue());
                break;
            case 4:
                DrawCircle((coords.first * 20 + 5) / (mapDimensions.first / 42.0f), (coords.second * 20 + 10) / (mapDimensions.second / 42.0f), 3 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), raylib::Color::SkyBlue());
                break;
        }
    }
    for (auto &egg: _GEH.getEggs()) {
        const tileCoordinates coords = egg.second.getCoords();
        DrawCircle((coords.first * 20 + 18) / (mapDimensions.first / 42.0f), (coords.second * 20 + 18) / (mapDimensions.second / 42.0f), 2 / ((mapDimensions.first / 42.0f) < (mapDimensions.second / 42.0f) ? (mapDimensions.first / 42.0f) : (mapDimensions.second / 42.0f)), getTeamColor(egg.second.getTeamName()));
    }
    auto dyingPlayers = _GEH.getDyingPlayers();
    for (auto dyingPlayer: dyingPlayers) {
        _GEH.removeDyingPlayer(dyingPlayer.second.getId());
    }
}

void zappy::RaylibGraphical::displayLowObjectTileInfo(zappy::tileCoordinates coords)
{
    // Changer les positions pour afficher en dessous de la map
    Tile &tile = _map.getTile(coords);
    std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
    if (entities.size() != 7)
        return;
    const int renderHeight = _window.GetRenderHeight();

    drawText("Tile " + std::to_string(coords.first) + " " + std::to_string(coords.second) + " infos", 15, renderHeight - 150, raylib::Color::White());

    // Cannot use drawMaterials here as the X and Y are on different columns
    drawText(std::to_string(entities[0]->getAmount()) + " Food", 15, renderHeight - 130, raylib::Color::Brown());
    drawText(std::to_string(entities[1]->getAmount()) + " Linemate", 15, renderHeight - 110, raylib::Color::Yellow());
    drawText(std::to_string(entities[2]->getAmount()) + " Deraumere", 15, renderHeight - 90, raylib::Color::Green());
    drawText(std::to_string(entities[3]->getAmount()) + " Sibur", 15, renderHeight - 70, raylib::Color::Red());
    drawText(std::to_string(entities[4]->getAmount()) + " Mendiane", 150, renderHeight - 130, raylib::Color::SkyBlue());
    drawText(std::to_string(entities[5]->getAmount()) + " Phiras", 150, renderHeight - 110, raylib::Color::DarkBlue());
    drawText(std::to_string(entities[6]->getAmount()) + " Thystame", 150, renderHeight - 90,raylib::Color::Purple());
}

void zappy::RaylibGraphical::drawParticles(zappy::tileCoordinates coords, raylib::Color color)
{
    RaylibParticles &particles = _particles.at(coords);
    particles.update();
    std::array<std::optional<ParticlesData>, MAX_PARTICLES> dataArray = particles.getDataArray();
    int head = particles.getHead();

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
    if (entities.size() != 7)
        return;
    std::array<int, 7> resources = entitiesToResources(entities);

    rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Tile " + std::to_string(coords.first) + " " + std::to_string(coords.second) + " infos", 15, 15, raylib::Color::Black());

    drawMaterials(resources, 20, 35);
}

void zappy::RaylibGraphical::displayLowObjectBroadcast()
{
    const int width = _window.GetRenderWidth();

    drawText("Broadcast", width - 225, 410, raylib::Color::White());
    while (_GEH.getBroadcast().size() > 0) {
        std::pair<int, std::string> message = _GEH.popMessage();
        std::string messageToDisplay = std::to_string(message.first) + ": " + message.second;
        _broadcastToDisplay.push_back(messageToDisplay);
    }
    while (_broadcastToDisplay.size() > 28) {
        _broadcastToDisplay.erase(_broadcastToDisplay.begin());
    }
    int pos = 430;
    for (std::string msg: _broadcastToDisplay) {
        drawText(msg, width - 315, pos, raylib::Color::White());
        pos += 20;
    }
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
        std::string messageToDisplay = std::to_string(message.first) + ": " + message.second;
        _broadcastToDisplay.push_back(messageToDisplay);
    }
    while (_broadcastToDisplay.size() > 7) {
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
    std::map<tileCoordinates, raylib::Color> map;
    for (auto &player: _GEH.getPlayers()) {
        player.second.updateDisplayPos();
        const floatCoordinates playerCoords = player.second.getDisplayCoords();
        Vector3 rotationAxis(0, 0.1, 0);
        float rotationAngle = static_cast<float>(zappy::Utils::getOrientation(player.second.getOrientation())) + 90.0f;

        Vector3 playerPosition(playerCoords.first - mapDimensions.first / 2.0f + 0.5, 0.1, playerCoords.second - mapDimensions.second / 2.0f + 0.5);
        Vector3 playerScale(0.1, 0.1, 0.1);

        _modelHolder.getPlayerModel().Draw(playerPosition, rotationAxis, rotationAngle, playerScale, getTeamColor(player.second.getTeamName()));

        if (player.second.isIncantating()) {
            map.insert_or_assign(player.second.getCoords(), getTeamColor(player.second.getTeamName()));
            const tileCoordinates coords = player.second.getCoords();
            try {
                _particles.at(coords);
            } catch (std::out_of_range) {
                _particles.insert({coords, RaylibParticles(coords, mapDimensions)});
            }
        }
        if (player.second.getSelected()) {
            // Highlight the player skeleton
            _modelHolder.getPlayerModel().DrawWires(playerPosition, rotationAxis, rotationAngle, playerScale);

            highlightPlayerFOV(player.second);
        }
        if (_animationToggle)
            updatePlayerAnimations(player.second);
    }
    for (auto &egg: _GEH.getEggs()) {
        const floatCoordinates eggCoords = egg.second.getDisplayCoords();
        _modelHolder.getEggModel().Draw(Vector3(eggCoords.first - mapDimensions.first / 2.0f + 0.5, 0.15, eggCoords.second - mapDimensions.second / 2.0f + 0.8), 0.25f);
    }
    for (auto &tileAndColor: map) {
        drawParticles(tileAndColor.first, tileAndColor.second);
    }
    auto dyingPlayers = _GEH.getDyingPlayers();
    for (auto dyingPlayer: dyingPlayers) {
        updateDyingPlayerAnimaions(dyingPlayer.second);
    }
}

void zappy::RaylibGraphical::updateDyingPlayerAnimaions(PlayerInfo &info)
{
    const int playerID = info.getId();

    try {
        _dyingPlayerAnimationsMap.at(playerID);
    } catch (std::out_of_range) {
        _dyingPlayerAnimationsMap.insert({playerID, std::pair(ROBOT_DEATH, 0)});
    }
    const std::pair<int, int> mapDimensions = _map.getDimensions();
    std::pair<int, int> &animIndexAndFrame = _dyingPlayerAnimationsMap.at(playerID);
    const floatCoordinates playerCoords = info.getDisplayCoords();
    Vector3 rotationAxis(0, 0.1, 0);
    float rotationAngle = static_cast<float>(zappy::Utils::getOrientation(info.getOrientation())) + 90.0f;
    Vector3 playerPosition(playerCoords.first - mapDimensions.first / 2.0f + 0.5, 0.1, playerCoords.second - mapDimensions.second / 2.0f + 0.5);
    Vector3 playerScale(0.1, 0.1, 0.1);

    ModelAnimation *animations = _modelHolder.getPlayerAnimations();
    _modelHolder.getPlayerModel().UpdateAnimation(animations[animIndexAndFrame.first], animIndexAndFrame.second);
    _modelHolder.getPlayerModel().Draw(playerPosition, rotationAxis, rotationAngle, playerScale, getTeamColor(info.getTeamName()));
    _modelHolder.getPlayerModel().UpdateAnimation(animations[ROBOT_IDLE], 0);
    if (animIndexAndFrame.second == animations[animIndexAndFrame.first].keyframeCount) {
        _GEH.removeDyingPlayer(playerID);
    }
    animIndexAndFrame.second++;
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
    definePlayerAnimation(info, animIndexAndFrame);
    ModelAnimation anim = _modelHolder.getPlayerAnimations()[animIndexAndFrame.first];
    _modelHolder.getPlayerModel().UpdateAnimation(anim, animIndexAndFrame.second);
    animIndexAndFrame.second++;
    if (animIndexAndFrame.second > anim.keyframeCount)
        animIndexAndFrame.second = 0;
}

void zappy::RaylibGraphical::definePlayerAnimation(PlayerInfo &info, std::pair<int, int> &animIndexAndFrame)
{
    if (info.isHitting()) {
        animIndexAndFrame.first = ROBOT_HIT;
        if (animIndexAndFrame.second == _modelHolder.getPlayerAnimations()[animIndexAndFrame.first].keyframeCount)
            _GEH.getPlayer(info.getId()).setHitting(false);
        return;
    }
    if (info.isTaking()) {
        animIndexAndFrame.first = ROBOT_TAKE;
        if (animIndexAndFrame.second == _modelHolder.getPlayerAnimations()[animIndexAndFrame.first].keyframeCount)
            _GEH.getPlayer(info.getId()).setTaking(false);
        return;
    }
    if (info.isDropping()) {
        animIndexAndFrame.first = ROBOT_DROP;
        if (animIndexAndFrame.second == _modelHolder.getPlayerAnimations()[animIndexAndFrame.first].keyframeCount)
            _GEH.getPlayer(info.getId()).setDropping(false);
        return;
    }
    if (info.isMoving()) {
        animIndexAndFrame.first = ROBOT_RUN;
    } else if (info.isIncantating()) {
        animIndexAndFrame.first = ROBOT_INCANTATION;
    } else {
        animIndexAndFrame.first = ROBOT_IDLE;
    }
}

void zappy::RaylibGraphical::drawPlayerInfo(PlayerInfo &info)
{
    const float posX = _window.GetRenderWidth() / 10.0;

    raylib::Rectangle rect(posX * 5.45, 20, 250, 90);
    const tileCoordinates coords = info.getCoords();
    rect.Draw(Fade(getTeamColor(info.getTeamName()), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Player " + std::to_string(info.getId()) + " Infos", posX * 5.5, 30, raylib::Color::Black());
    drawText("Part of " + info.getTeamName() + " team", posX * 5.5, 50, raylib::Color::Black());
    drawText("Level " + std::to_string(info.getLevel()), posX * 5.5, 70, raylib::Color::Black());
    drawText("On tile " + std::to_string(coords.first) + " " + std::to_string(coords.second), posX * 5.5, 90, raylib::Color::Black());

    auto inventory = info.getInventory();
    raylib::Rectangle otherRect(posX * 7.95, 20, 185, 180);
    otherRect.Draw(Fade(getTeamColor(info.getTeamName()), 0.5f));
    otherRect.DrawLines(Fade(raylib::Color::Black(), 0.8f));

    drawText("Player Inventory", posX * 8, 30, raylib::Color::Black());

    std::array<int, 7> resources = {{
        inventory.at("food"),
        inventory.at("Linemate"),
        inventory.at("Deraumere"),
        inventory.at("Sibur"),
        inventory.at("Mendiane"),
        inventory.at("Phiras"),
        inventory.at("Thystame"),
    }};

    drawMaterials(resources, posX * 8, 50);
}

void zappy::RaylibGraphical::drawEggInfo(Egg &egg)
{
    const float posX = _window.GetRenderWidth() / 10.0;

    raylib::Rectangle rect(posX * 8, 20, 250, 90);
    const tileCoordinates coords = egg.getCoords();
    if (egg.getTeamName() == "")
        rect.Draw(Fade(raylib::Color::Gray(), 0.5f));
    else
        rect.Draw(Fade(getTeamColor(egg.getTeamName()), 0.5f));
    rect.DrawLines(Fade(raylib::Color::Black(), 0.8f));
    drawText("Egg " + std::to_string(egg.getId()) + " Infos", posX * 8, 30, raylib::Color::Black());
    if (egg.getTeamName() == "") {
        drawText("Not part of a team yet", posX * 8, 50, raylib::Color::Black());
    } else {
        drawText("Part of " + egg.getTeamName() + " team", posX * 8, 70, raylib::Color::Black());
    }
    drawText("On tile " + std::to_string(coords.first) + " " + std::to_string(coords.second), posX * 8, 90, raylib::Color::Black());
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
        DrawCubeWires(convertVector3D(tile.getDisplayCoordinates()), 1.0f, 0.1f, 1.0f, getTeamColor(info.getTeamName()));
        for (int j = 0; j < i + 1; j++) {
            tile = _map.getTile(zappy::Utils::handleTileOverflow(tileCoordinates((coords.first + vals.fx * (i + 1)) - (vals.sx * (j + 1)) , (coords.second + vals.fy * (i + 1)) - (vals.sy * (j + 1))), mapDimensions));
            DrawCubeWires(convertVector3D(tile.getDisplayCoordinates()), 1.0f, 0.1f, 1.0f, getTeamColor(info.getTeamName()));

            tile = _map.getTile(zappy::Utils::handleTileOverflow(tileCoordinates((coords.first + vals.fx * (i + 1)) + (vals.sx * (j + 1)) , (coords.second + vals.fy * (i + 1)) + (vals.sy * (j + 1))), mapDimensions));
            DrawCubeWires(convertVector3D(tile.getDisplayCoordinates()), 1.0f, 0.1f, 1.0f, getTeamColor(info.getTeamName()));
        }
    }
}

raylib::Color zappy::RaylibGraphical::getTeamColor(std::string name)
{
    if (name == "") {
        return raylib::Color::White();
    }
    raylib::Color color(rand() % 255, rand() % 255, rand() % 255);

    try {
        color = _colorMap.at(name);
    } catch (std::out_of_range) {
        _colorMap.insert({name, color});
    }
    return color;
}

bool zappy::RaylibGraphical::endScreen(std::string teamName)
{
    bool exit = false;
    Vector2 size = _window.GetSize();
    std::string Title = "The winner team is " + teamName;
    const float font = 35;

    if (_window.ShouldClose()) {
        exit = true;
    }

    _modelHolder.updateMusic();
    _window.BeginDrawing();
    _window.ClearBackground(raylib::Color::RayWhite());
    int scroll = _modelHolder.updateEndBackgroundScroll();
    raylib::Texture2D& bkg = _modelHolder.getEndScreen();
    bkg.Draw(Vector2(0, scroll), 0.0f, 0.5f, raylib::Color::White());
    bkg.Draw(Vector2(0, -(bkg.height * 0.5) + scroll), 0.0f, 0.5f, raylib::Color::White());

    raylib::DrawText(Title, size.x / 2 - (Title.length() * font) / 4, size.y / 2, font, BLACK);

    _window.EndDrawing();
    return exit;
}

void zappy::RaylibGraphical::drawMaterials(std::array<int, 7> resources, int x, int initialY)
{
    drawText(std::to_string(resources[0]) + " Food", x, initialY, raylib::Color::Brown());
    drawText(std::to_string(resources[1]) + " Linemate", x, initialY + 20, raylib::Color::Yellow());
    drawText(std::to_string(resources[2]) + " Deraumere", x, initialY + 40, raylib::Color::Green());
    drawText(std::to_string(resources[3]) + " Sibur", x, initialY + 60, raylib::Color::Red());
    drawText(std::to_string(resources[4]) + " Mendiane", x, initialY + 80, raylib::Color::SkyBlue());
    drawText(std::to_string(resources[5]) + " Phiras", x, initialY + 100, raylib::Color::DarkBlue());
    drawText(std::to_string(resources[6]) + " Thystame", x, initialY + 120,raylib::Color::Purple());
}

raylib::Vector3 zappy::RaylibGraphical::convertVector3D(zappy::Vector3D vec)
{
    return raylib::Vector3 {vec.x, vec.y, vec.z};
}

std::array<int, 7> zappy::RaylibGraphical::entitiesToResources(std::vector<std::shared_ptr<IEntity>> &entities)
{
    std::array<int, 7> resources;
    resources.fill(0);

    if (entities.size() != 7)
        return resources;

    for (unsigned int i = 0; i < 7; i++) {
        resources[i] = entities[i]->getAmount();
    }
    return resources;
}
