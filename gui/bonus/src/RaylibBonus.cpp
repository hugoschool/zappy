#include "RaylibBonus.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "Map.hpp"
#include "Raylib.hpp"
#include "SafeQueue.hpp"
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
    _screen(screen::MENU), _fontSize(40.0), _index(0)
{}

zappy::RaylibBonus::~RaylibBonus()
{}

bool zappy::RaylibBonus::runMenu(zappy::SafeQueue<std::string> &queue, std::vector<std::string> &teams)
{
    std::vector<raylib::Rectangle> vecRec;
    raylib::Vector2 size = _window.GetSize();

    if (_window.ShouldClose())
        return true;

    if (raylib::Keyboard::IsKeyPressed(KEY_SPACE)) {
        _screen = screen::GAMEPLAY;
        queue.push(teams.at(_index) + "\n");
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

bool zappy::RaylibBonus::runGameplay(zappy::SafeQueue<std::string> &cmds)
{
    if (raylib::Keyboard::IsKeyPressed(KEY_W)) {
        cmds.push("Forward\n");
        cmds.push("Take food\n");
    }
    if (raylib::Keyboard::IsKeyPressed(KEY_A))
        cmds.push("Left\n");
    if (raylib::Keyboard::IsKeyPressed(KEY_D))
        cmds.push("Right\n");

    // maybe change some keybids
    if (raylib::Keyboard::IsKeyPressed(KEY_E))
        cmds.push("Take object\n");
    if (raylib::Keyboard::IsKeyPressed(KEY_Q))
        cmds.push("Eject\n");
    if (raylib::Keyboard::IsKeyPressed(KEY_L))
        cmds.push("Look\n");
    return run();
}

bool zappy::RaylibBonus::runScreens(zappy::SafeQueue<std::string> &cmds, std::vector<std::string> &teams)
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
    float sizeX = _window.GetSize().GetX();
    float sizeY = _window.GetSize().GetY();
    float width = sizeX / 20;

    std::array<std::string, 6> items = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    std::array<raylib::Color, 6> colors = {GRAY, GREEN, RED, SKYBLUE, DARKBLUE, PURPLE};
    std::vector<raylib::Rectangle> recs;

    for (size_t i = 0; i < items.size(); i++)
        recs.push_back(raylib::Rectangle({width * (2 + i), sizeY - (width * 2)}, {width, width}));

    for (size_t i = 0; i < items.size(); i++) {
        recs.at(i).Draw(colors[i]);
        if (static_cast<size_t>(_index) == i)
            recs.at(i).DrawLines(BLACK);
    }
}

void zappy::RaylibBonus::interpretInputs()
{
    if (raylib::Keyboard::IsKeyPressed(KEY_LEFT)) {
        _index--;
        if (_index < 0)
            _index = 6 - 1;
    }

    if (raylib::Keyboard::IsKeyPressed(KEY_RIGHT))
        _index = (_index + 1) % 6;
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
    interpretInputs();
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
