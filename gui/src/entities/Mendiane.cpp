#include "entities/Mendiane.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>
#include <raylib.h>
#include <utility>

zappy::Mendiane::Mendiane(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Mendiane, tile, amount)
{}

zappy::Mendiane::~Mendiane()
{}

raylib::Color zappy::Mendiane::getMaterialColor()
{
    return raylib::Color::SkyBlue();
}

Vector3 zappy::Mendiane::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.45 + 0.5f);
}
