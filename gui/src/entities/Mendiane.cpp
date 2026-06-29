#include "entities/Mendiane.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <utility>

zappy::Mendiane::Mendiane(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Mendiane, tile, amount)
{}

zappy::Mendiane::~Mendiane()
{}

std::tuple<int, int, int> zappy::Mendiane::getMaterialColor()
{
    return std::tuple(102, 191, 255);
}

std::pair<float, float> zappy::Mendiane::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return std::pair<float, float>(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, zComponent + 0.45 + 0.5f);
}
