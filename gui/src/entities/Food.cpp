#include "entities/Food.hpp"
#include "IEntity.hpp"
#include "ModelHolder.hpp"
#include "entities/AEntity.hpp"
#include <iostream>

zappy::Food::Food(zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount)
{}

zappy::Food::~Food()
{}

void zappy::Food::draw(zappy::ModelHolder& modelHolder, std::pair<int, int> dimensions)
{
    if (_amount == 0)
        return;
    float heightVal = 0.05;
    for (int i = 0; i < _amount; i++) {
        modelHolder.getFoodModel().Draw(Vector3(_coords.first - (dimensions.first / 2.0f) - 0.2 + 0.5f, heightVal, _coords.second - (dimensions.second / 2.0f) + 0.5f), 1.0f);
        heightVal += 0.05;
    }
}
