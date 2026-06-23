#include "RaylibBonus.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "Map.hpp"
#include "Raylib.hpp"
#include "SafeQueue.hpp"
#include <Functions.hpp>
#include <Keyboard.hpp>
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
