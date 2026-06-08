#include "Map.hpp"
#include "IEntity.hpp"
#include "Tile.hpp"

zappy::Map::Map(int X, int Y) : _tiles(), _dimensions(std::pair(X, Y))
{
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            _tiles.insert({tileCoordinates(x, y), Tile(x, y)});
        }
    }
}

zappy::Map::~Map()
{}

zappy::Tile zappy::Map::getTile(zappy::tileCoordinates coords) const
{
    return _tiles.at(coords);
}

const std::pair<int, int> zappy::Map::getDimensions() const
{
    return _dimensions;
}
