#include "entities/Materials.hpp"
#include "IRaylibEntities.hpp"
#include "RaylibModelHolder.hpp"
#include "entities/AEntity.hpp"
#include "Raylib.hpp"

zappy::Material::Material(zappy::MaterialType type): zappy::AEntity({0, 0}, 0), _type(type)
{}

zappy::Material::Material(zappy::MaterialType type, zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount), _type(type)
{}

zappy::Material::~Material()
{}

raylib::Color zappy::Material::getMaterialColor()
{
    switch (_type) {
        case Linemate:
            return raylib::Color::Yellow();
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

Vector3 zappy::Material::getMaterialPosition(std::pair<int, int> dimensions)
{
    float zComponent = _coords.second - (dimensions.second / 2.0f) - 0.4;
    switch (_type) {
        case Linemate:
            return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.5f);
        case Deraumere:
            return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.15 + 0.5f);
        case Sibur:
            return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.3 + 0.5f);
        case Mendiane:
            return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.45 + 0.5f);
        case Phiras:
            return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.6 + 0.5f);
        case Thystame:
            return Vector3(_coords.first - (dimensions.first / 2.0f) - 0.4 + 0.5f, 0.05, zComponent + 0.75 + 0.5f);
    }
}

zappy::MaterialType zappy::Material::getMaterialType() const
{
    return _type;
}

void zappy::Material::draw(zappy::RaylibModelHolder& RaylibModelHolder, std::pair<int, int> dimensions)
{
    if (_amount == 0)
        return;
    const raylib::Color color = getMaterialColor();
    const Vector3 position = getMaterialPosition(dimensions);
    RaylibModelHolder.getMaterialModel().Draw(position, 0.5f, color);
}

void zappy::Material::drawLowObject(std::pair<int, int> dimensions)
{
    if (dimensions.first > 20)
        return;
    std::string str = std::to_string(_amount);
    const int posYAdd = (_type + 2) * (20 / 7);
    raylib::DrawText(str.c_str(), (_coords.first * 20 + 1) / (dimensions.first / 42.0f), (_coords.second * 20 + posYAdd) / (dimensions.second / 42.0f), 3 / ((dimensions.first / 42.0f) < (dimensions.second / 42.0f) ? (dimensions.first / 42.0f) : (dimensions.second / 42.0f)), getMaterialColor());
}
