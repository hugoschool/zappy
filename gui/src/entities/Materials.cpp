#include "entities/Materials.hpp"
#include "IEntity.hpp"
#include "entities/AEntity.hpp"
zappy::Material::Material(): AEntity()
{}

zappy::Material::Material(zappy::tileCoordinates coords): AEntity(coords)
{}

zappy::Material::~Material()
{}

void zappy::Material::draw()
{
    return;
}
