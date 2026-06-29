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

void zappy::Material::draw(zappy::IModelHolder& modelHolder, std::pair<int, int> dimensions)
{
    if (_amount == 0)
        return;
    RaylibModelHolder *raylibModelHolder = dynamic_cast<RaylibModelHolder*>(&modelHolder);
    if (raylibModelHolder != nullptr) {
        const raylib::Color color = getMaterialColor();
        const Vector3 position = getMaterialPosition(dimensions);
        raylibModelHolder->getMaterialModel().Draw(position, 0.5f, color);
    }
}

void zappy::Material::drawLowObject(std::pair<int, int> dimensions)
{
    if (dimensions.first > 20)
        return;
    std::string str = std::to_string(_amount);
    const int posYAdd = (static_cast<int>(_type) + 2) * (20 / 7);
    raylib::DrawText(str.c_str(), (_coords.first * 20 + 1) / (dimensions.first / 42.0f), (_coords.second * 20 + posYAdd) / (dimensions.second / 42.0f), 3 / ((dimensions.first / 42.0f) < (dimensions.second / 42.0f) ? (dimensions.first / 42.0f) : (dimensions.second / 42.0f)), getMaterialColor());
}
