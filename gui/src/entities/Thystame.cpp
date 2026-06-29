#include "entities/Thystame.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>
#include <raylib.h>
#include <utility>

zappy::Thystame::Thystame(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Thystame, tile, amount)
{}

zappy::Thystame::~Thystame()
{}

raylib::Color zappy::Thystame::getMaterialColor()
{
    return raylib::Color::DarkBlue();
}

Vector3 zappy::Thystame::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.6 + 0.5f);
}
