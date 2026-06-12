#include "entities/Egg.hpp"
#include "IEntity.hpp"
#include "ModelHolder.hpp"
#include "entities/AEntity.hpp"

zappy::Egg::Egg(zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount)
{}

zappy::Egg::~Egg()
{}

void zappy::Egg::draw(zappy::ModelHolder& modelHolder, std::pair<int, int> dimensions)
{
    modelHolder.getEggModel().Draw(Vector3(_coords.first - (dimensions.first / 2.0f) + 0.5f, 0.025, _coords.second - (dimensions.second / 2.0f)  + 0.5f), 0.1);
}
