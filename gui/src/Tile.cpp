#include "Tile.hpp"
#include <cstddef>
#include <memory>

zappy::Tile::Tile() : _coords(0, 0), _entities()
{
}

zappy::Tile::Tile(int X, int Y) : _coords(X, Y), _entities()
{
}

zappy::Tile::~Tile()
{
}

zappy::tileCoordinates zappy::Tile::getCoords() const
{
    return _coords;
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
