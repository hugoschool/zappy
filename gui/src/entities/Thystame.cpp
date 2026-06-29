#include "entities/Thystame.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <utility>

zappy::Thystame::Thystame(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Thystame, tile, amount)
{}

zappy::Thystame::~Thystame()
{}

std::tuple<int, int, int> zappy::Thystame::getMaterialColor()
{
    return std::tuple(200, 122, 255);
}

std::pair<float, float> zappy::Thystame::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return std::pair<float, float>(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, zComponent + 0.6 + 0.5f);
}
