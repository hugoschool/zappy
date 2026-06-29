
#include "entities/MaterialFactory.hpp"
#include "IEntity.hpp"
#include "entities/Deraumere.hpp"
#include "entities/Linemate.hpp"
#include "entities/Materials.hpp"
#include "entities/Mendiane.hpp"
#include "entities/Phiras.hpp"
#include "entities/Sibur.hpp"
#include "entities/Thystame.hpp"
#include <memory>

zappy::MaterialFactory::MaterialFactory() : _materials()
{
    _materials.insert({MaterialType::Linemate, [](tileCoordinates pos, int amount) {return std::make_shared<Linemate>(pos, amount);}});
    _materials.insert({MaterialType::Deraumere, [](tileCoordinates pos, int amount) {return std::make_shared<Deraumere>(pos, amount);}});
    _materials.insert({MaterialType::Sibur, [](tileCoordinates pos, int amount) {return std::make_shared<Sibur>(pos, amount);}});
    _materials.insert({MaterialType::Mendiane, [](tileCoordinates pos, int amount) {return std::make_shared<Mendiane>(pos, amount);}});
    _materials.insert({MaterialType::Phiras, [](tileCoordinates pos, int amount) {return std::make_shared<Phiras>(pos, amount);}});
    _materials.insert({MaterialType::Thystame, [](tileCoordinates pos, int amount) {return std::make_shared<Thystame>(pos, amount);}});
}

zappy::MaterialFactory::~MaterialFactory()
{}

std::shared_ptr<zappy::IEntity> zappy::MaterialFactory::getMaterial(zappy::MaterialType type, zappy::tileCoordinates pos, int amout)
{
    return _materials.at(type)(pos, amout);
}
