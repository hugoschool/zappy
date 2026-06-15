#include "Tile.hpp"
#include <cstddef>
#include <memory>
#include <utility>


zappy::Tile::Tile(int X, int Y, std::pair<int, int> mapDimensions) : _coords(X, Y), _displayCoordinates(static_cast<float>(X) - mapDimensions.first / 2.0f + 0.5f, 0.0f, static_cast<float>(Y) - mapDimensions.second / 2.0f + 0.5f), _entities(), _selected(false)
{
}

zappy::Tile::~Tile()
{
}

zappy::tileCoordinates zappy::Tile::getCoords() const
{
    return _coords;
}

Vector3 zappy::Tile::getDisplayCoordinates() const
{
    return _displayCoordinates;
}

void zappy::Tile::setDisplayCoordinates(Vector3 displayCoordinates)
{
    _displayCoordinates = displayCoordinates;
}

void zappy::Tile::addEntity(std::shared_ptr<IEntity> entity)
{
    _entities.push_back(std::move(entity));
}

void zappy::Tile::removeEntity(std::shared_ptr<IEntity> entity)
{
    for (std::size_t i = 0; i < _entities.size(); i++) {
        if (_entities[i] == entity) {
            _entities.erase(_entities.begin() + i);
        }
    }
}

std::vector<std::shared_ptr<zappy::IEntity>>& zappy::Tile::getEntities()
{
    return _entities;
}

void zappy::Tile::clear()
{
    _entities.clear();
}

void zappy::Tile::setSelectedState(bool selectedState)
{
    _selected = selectedState;
}

bool zappy::Tile::isSelected()
{
    return _selected;
}
