#include "entities/Sibur.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <utility>

zappy::Sibur::Sibur(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Sibur, tile, amount)
{}

zappy::Sibur::~Sibur()
{}

std::tuple<int, int, int> zappy::Sibur::getMaterialColor()
{
    return std::tuple(230, 41, 55);
}

std::pair<float, float> zappy::Sibur::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return std::pair<float, float>(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, zComponent + 0.3 + 0.5f);
}
