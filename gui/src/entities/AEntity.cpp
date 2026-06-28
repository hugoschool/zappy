#include "entities/AEntity.hpp"
#include "IEntity.hpp"


zappy::AEntity::AEntity(zappy::tileCoordinates coords, int amount) : _coords(coords), _amount(amount)
{
}

zappy::AEntity::~AEntity()
{}

zappy::tileCoordinates zappy::AEntity::getCoords() const
{
    return _coords;
}

int zappy::AEntity::getAmount() const
{
    return _amount;
}
