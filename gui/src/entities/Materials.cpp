#include "entities/Materials.hpp"
#include "IEntity.hpp"
#include "ModelHolder.hpp"
#include "entities/AEntity.hpp"

zappy::Material::Material(zappy::MaterialType type): zappy::AEntity(), _type(type)
{}

zappy::Material::Material(zappy::MaterialType type, zappy::tileCoordinates coords): zappy::AEntity(coords), _type(type)
{}

zappy::Material::~Material()
{}

raylib::Color zappy::Material::getMaterialColor()
{
    switch (_type) {
        case Linemate:
            return raylib::Color::Black();
        case Deraumere:
            return raylib::Color::Green();
        case Sibur:
            return raylib::Color::Red();
        case Mendiane:
            return raylib::Color::SkyBlue();
        case Phiras:
            return raylib::Color::DarkBlue();
        case Thystame:
            return raylib::Color::Purple();
    }
}

void zappy::Material::draw(zappy::ModelHolder& modelHolder)
{
    modelHolder.getMaterialModel().Draw(Vector3(_coords.first - 5, 0.1, _coords.second - 5), 1.0f, getMaterialColor());
}
