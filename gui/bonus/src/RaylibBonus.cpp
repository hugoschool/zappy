#include "RaylibBonus.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "Map.hpp"
#include "Raylib.hpp"
#include "SafeQueue.hpp"
#include <Keyboard.hpp>
#include <raylib.h>
#include <string>

zappy::RaylibBonus::RaylibBonus(zappy::Map &map, GameplayEntitiesHolder &GEH) : RaylibGraphical(map, GEH)
{}

zappy::RaylibBonus::~RaylibBonus()
{}

bool zappy::RaylibBonus::runCommands(zappy::SafeQueue<std::string> &cmds)
{
    if (raylib::Keyboard::IsKeyPressed(KEY_W))
        cmds.push("Forward\n");
    return run();
}
