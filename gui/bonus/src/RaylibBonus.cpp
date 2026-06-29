#include "RaylibBonus.hpp"
#include "CircularBuffer.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "Map.hpp"
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
#include <raylib.h>
#include <string>
#include <vector>

zappy::RaylibBonus::RaylibBonus(zappy::Map &map, GameplayEntitiesHolder &GEH) : RaylibGraphical(map, GEH),
    _screen(screen::MENU), _fontSize(40.0), _index(0), _sizeX(_window.GetSize().GetX()),
    _sizeY(_window.GetSize().GetY()), _width(_sizeX / 20),
    _items({"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"}),
    _colors({GRAY, GREEN, RED, SKYBLUE, DARKBLUE, PURPLE}),
    _itemRec()
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

    if (raylib::Keyboard::IsKeyPressed(KEY_SPACE)) {
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
            _index = 6 - 1;
    }
    if (raylib::Keyboard::IsKeyPressed(KEY_RIGHT))
        _index = (_index + 1) % 6;

    if (raylib::Keyboard::IsKeyPressed(KEY_E)) {
        cmds.addElement("Take " + _items.at(_index) + "\n");
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
    updateCamera();

    if (_window.ShouldClose()) {
        exit = true;
    }
    if (raylib::Keyboard::IsKeyPressed(KEY_P))
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

    displayItems();

    _window.DrawFPS(920, 10);

    _window.EndDrawing();
    return exit;
}
