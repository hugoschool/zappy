#include "RaylibBonus.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "Map.hpp"
#include "Raylib.hpp"
#include "SafeQueue.hpp"
#include <Keyboard.hpp>
#include <raylib.h>
#include <string>

zappy::RaylibBonus::RaylibBonus(zappy::Map &map, GameplayEntitiesHolder &GEH) : RaylibGraphical(map, GEH),
    _screen(screen::GAMEPLAY)
{}

zappy::RaylibBonus::~RaylibBonus()
{}

bool zappy::RaylibBonus::runMenu(zappy::SafeQueue<std::string> &)
{
    return true;
}

bool zappy::RaylibBonus::runGameplay(zappy::SafeQueue<std::string> &cmds)
{
    if (raylib::Keyboard::IsKeyPressed(KEY_W))
        cmds.push("Forward\n");
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

bool zappy::RaylibBonus::runCommands(zappy::SafeQueue<std::string> &cmds)
{
    switch (_screen) {
        case screen::MENU:
            return runMenu(cmds);
        case screen::GAMEPLAY:
            return runGameplay(cmds);
        default:
            return true;
    }
}
