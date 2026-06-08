#include "entities/Food.hpp"
#include "IEntity.hpp"
#include "entities/AEntity.hpp"
zappy::Food::Food(): AEntity()
{}

zappy::Food::Food(zappy::tileCoordinates coords): AEntity(coords)
{}

zappy::Food::~Food()
{}

void zappy::Food::draw()
{
    return;
}
