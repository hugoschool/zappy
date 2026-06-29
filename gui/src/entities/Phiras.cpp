#include "entities/Phiras.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <utility>

zappy::Phiras::Phiras(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Phiras, tile, amount)
{}

zappy::Phiras::~Phiras()
{}

std::tuple<int, int, int> zappy::Phiras::getMaterialColor()
{
    return std::tuple(0, 82, 172);
}

std::pair<float, float> zappy::Phiras::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return std::pair<float, float>(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, zComponent + 0.6 + 0.5f);
}
