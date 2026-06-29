#include "RaylibBonus.hpp"
#include "CircularBuffer.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "IEntity.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Raylib.hpp"
#include <Color.hpp>
#include <Functions.hpp>
#include <Keyboard.hpp>
#include <Mouse.hpp>
#include <Rectangle.hpp>
#include <Text.hpp>
#include <Vector2.hpp>
#include <array>
#include <cstddef>
#include <optional>
#include <raylib.h>
#include <string>
#include <vector>

zappy::RaylibBonus::RaylibBonus(zappy::Map &map, GameplayEntitiesHolder &GEH) : RaylibGraphical(map, GEH),
    _screen(screen::MENU), _fontSize(40.0), _index(0), _sizeX(_window.GetSize().GetX()),
    _sizeY(_window.GetSize().GetY()), _width(_sizeX / 20),
    _items({"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "all"}),
    _colors({GRAY, GREEN, RED, SKYBLUE, DARKBLUE, PURPLE, BLACK}),
    _itemRec(), _cameraState(cameraState::GLOBAL)
{
    for (size_t i = 0; i < _items.size(); i++)
        _itemRec.push_back(raylib::Rectangle({_width * (2 + i), _sizeY - (_width * 2)}, {_width, _width}));
}

zappy::RaylibBonus::~RaylibBonus()
{}

bool zappy::RaylibBonus::runMenu(zappy::CircularBuffer<std::string> &buffer, std::vector<std::string> &teams)
{
    std::vector<raylib::Rectangle> vecRec;
    raylib::Vector2 size = _window.GetSize();

    if (_window.ShouldClose())
        return true;

    if (raylib::Keyboard::IsKeyPressed(KEY_SPACE) || raylib::Keyboard::IsKeyPressed(KEY_ENTER)) {
        _screen = screen::GAMEPLAY;
        buffer.addElement(teams.at(_index) + "\n");
        buffer.addElement("Broadcast PlayerPlayer\n");
        _index = 0;
    }

    if (raylib::Keyboard::IsKeyPressed(KEY_DOWN))
        _index = (_index + 1) % teams.size();

    if (raylib::Keyboard::IsKeyPressed(KEY_UP)) {
        _index--;
        if (_index < 0)
            _index = teams.size() - 1;
    }

    _window.BeginDrawing();
    _window.ClearBackground(WHITE);

    for (size_t i = 0; i < teams.size(); i++) {
        if (i == static_cast<size_t>(_index)) {
            raylib::Rectangle({size.GetX() / 2 - (teams.at(i).length() * (_fontSize + 7)) / 2, static_cast<float>(i) * (_fontSize + 3)},
            {static_cast<float>(teams.at(i).length() * (_fontSize  + 7)), _fontSize + 4}).Draw(RED);
        }
        raylib::Rectangle({size.GetX() / 2 - (teams.at(i).length() * (_fontSize + 5)) / 2, static_cast<float>(i) * (_fontSize + 5)},
        {static_cast<float>(teams.at(i).length() * (_fontSize  + 5)), _fontSize}).Draw(BLACK);
        raylib::DrawText(teams.at(i).c_str(), size.GetX() / 2 - (teams.at(i).length() * (_fontSize)) / 2,
        static_cast<float>(i) * (_fontSize + 5) + 5, _fontSize, WHITE);
    }

    _window.EndDrawing();
    return false;
}

bool zappy::RaylibBonus::runGameplay(zappy::CircularBuffer<std::string> &cmds)
{
    if (raylib::Keyboard::IsKeyPressed(KEY_W)) {
        cmds.addElement("Forward\n");
        cmds.addElement("Take food\n");
    }
    if (raylib::Keyboard::IsKeyPressed(KEY_A))
        cmds.addElement("Left\n");
    if (raylib::Keyboard::IsKeyPressed(KEY_D))
        cmds.addElement("Right\n");

    // maybe change some keybids
    if (raylib::Keyboard::IsKeyPressed(KEY_Q))
        cmds.addElement("Eject\n");
    if (raylib::Keyboard::IsKeyPressed(KEY_L))
        cmds.addElement("Look\n");

    if (raylib::Keyboard::IsKeyPressed(KEY_LEFT)) {
        _index--;
        if (_index < 0)
            _index = _items.size() - 1;
    }
    if (raylib::Keyboard::IsKeyPressed(KEY_RIGHT))
        _index = (_index + 1) % 7;

    if (raylib::Keyboard::IsKeyPressed(KEY_E)) {
        if (_items.at(_index) != "all") {
            cmds.addElement("Take " + _items.at(_index) + "\n");
        } else {
            for (size_t i = 0; i < _items.size() - 1; i++) {
                cmds.addElement("Take " + _items.at(i) + "\n");
            }
        }
    }

    return run();
}

bool zappy::RaylibBonus::runScreens(zappy::CircularBuffer<std::string> &cmds, std::vector<std::string> &teams)
{
    switch (_screen) {
        case screen::MENU:
            return runMenu(cmds, teams);
        case screen::GAMEPLAY:
            return runGameplay(cmds);
        default:
            return true;
    }
}

void zappy::RaylibBonus::displayItems()
{
    for (size_t i = 0; i < _items.size(); i++) {
        _itemRec.at(i).Draw(_colors[i]);
        if (static_cast<size_t>(_index) == i)
            _itemRec.at(i).DrawLines(BLACK);
    }
}

bool zappy::RaylibBonus::run()
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
        displayItems();
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

void zappy::RaylibBonus::updateCamera()
{
    std::optional<PlayerInfo> player = std::nullopt;

    for (auto connectedPlayer: _GEH.getPlayers()) {
        if (connectedPlayer.second.isPlayer() == true) {
            player = connectedPlayer.second;
        }
    }

    if (player.has_value() == false) {
        return;
    }

    // Change camera mode
    if (raylib::Keyboard::IsKeyPressed(KEY_C)) {
        switch (_cameraState) {
            case cameraState::BEHIND:
                _cameraState = cameraState::GLOBAL;
                break;
            case zappy::cameraState::GLOBAL:
                _cameraState = cameraState::BEHIND;
                break;
        }
    }

    Vector3 cameraPosition;
    Vector3 cameraTarget;

    floatCoordinates playerFloatPosition = player.value().getDisplayCoords();


    if (_cameraState == cameraState::BEHIND) {
        _camera.Update(CAMERA_CUSTOM);

        cameraPosition = Vector3(playerFloatPosition.first - _map.getDimensions().first / 2.0f + 0.5, 0.7, playerFloatPosition.second - _map.getDimensions().second / 2.0f + 0.5);
        cameraTarget = cameraPosition;

        std::pair<int, int> mapDimensions = _map.getDimensions();
        cameraTarget.y = 0;
        switch (player.value().getOrientation()) {
            case 1:
                cameraPosition.z += 1;
                cameraTarget.z -= mapDimensions.second;
                break;
            case 2:
                cameraPosition.x -= 1;
                cameraTarget.x += mapDimensions.first;
                break;
            case 3:
                cameraPosition.z -= 1;
                cameraTarget.z += mapDimensions.second;
                break;
            case 4:
                cameraPosition.x += 1;
                cameraTarget.x -= mapDimensions.first;
                break;
            default:
                break;
        }
        // Only done in this part
        _camera.SetPosition(cameraPosition);
    } else if (_cameraState == cameraState::GLOBAL) {
        // Camera angle moveable while holding the click.
        if (raylib::Mouse::IsButtonDown(MOUSE_BUTTON_RIGHT)) {
            _camera.Update(CAMERA_THIRD_PERSON);
        }
        if (raylib::Mouse::IsButtonUp(MOUSE_BUTTON_RIGHT)) {
            _camera.Update(CAMERA_CUSTOM);
        }

        // Handle scrolling
        float scroll = raylib::Mouse::GetWheelMove();
        if (scroll != 0) {
            _camera.Update(CAMERA_THIRD_PERSON);
        } else {
            _camera.Update(CAMERA_CUSTOM);
        }

        cameraTarget = Vector3(playerFloatPosition.first - _map.getDimensions().first / 2.0f + 0.5, 0.5, playerFloatPosition.second - _map.getDimensions().second / 2.0f + 0.5);
    }
    _camera.SetTarget(cameraTarget);
}
