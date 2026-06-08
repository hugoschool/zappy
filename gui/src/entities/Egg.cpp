#include "entities/Egg.hpp"
#include "IEntity.hpp"
#include "entities/AEntity.hpp"
zappy::Egg::Egg(): AEntity()
{}

zappy::Egg::Egg(zappy::tileCoordinates coords): AEntity(coords)
{}

zappy::Egg::~Egg()
{}

void zappy::Egg::draw()
{
    return;
}
