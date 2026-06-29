#include "entities/Materials.hpp"
#include "IEntity.hpp"
#include "IModelHolder.hpp"
#include "RaylibModelHolder.hpp"
#include "entities/AEntity.hpp"
#include "Raylib.hpp"

zappy::Material::Material(zappy::MaterialType type): zappy::AEntity({0, 0}, 0), _type(type)
{}

zappy::Material::Material(zappy::MaterialType type, zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount), _type(type)
{}

zappy::Material::~Material()
{}

zappy::MaterialType zappy::Material::getMaterialType() const
{
    return _type;
}
