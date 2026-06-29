#include "entities/Sibur.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>
#include <raylib.h>
#include <utility>

zappy::Sibur::Sibur(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Sibur, tile, amount)
{}

zappy::Sibur::~Sibur()
{}

raylib::Color zappy::Sibur::getMaterialColor()
{
    return raylib::Color::Red();
}

Vector3 zappy::Sibur::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.3 + 0.5f);
}
