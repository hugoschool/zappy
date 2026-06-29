#include "entities/Linemate.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <utility>

zappy::Linemate::Linemate(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Linemate, tile, amount)
{}

zappy::Linemate::~Linemate()
{}

std::tuple<int, int, int> zappy::Linemate::getMaterialColor()
{
    return std::tuple(253, 249, 0);
}

std::pair<float, float> zappy::Linemate::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return std::pair<float, float>(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, zComponent + 0.5f);
}
