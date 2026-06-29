#include "entities/Linemate.hpp"
#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>
#include <raylib.h>
#include <utility>

zappy::Linemate::Linemate(zappy::tileCoordinates tile, int amount) : Material(MaterialType::Linemate, tile, amount)
{}

zappy::Linemate::~Linemate()
{}

raylib::Color zappy::Linemate::getMaterialColor()
{
    return raylib::Color::Yellow();
}

Vector3 zappy::Linemate::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.5f);
}
