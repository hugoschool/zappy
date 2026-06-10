#include "entities/Egg.hpp"
#include "IEntity.hpp"
#include "ModelHolder.hpp"
#include "entities/AEntity.hpp"

zappy::Egg::Egg(zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount)
{}

zappy::Egg::~Egg()
{}

void zappy::Egg::draw(zappy::ModelHolder& modelHolder)
{
    modelHolder.getEggModel().Draw(Vector3(_coords.first - 5, 0.025, _coords.second - 5), 0.1);
}
