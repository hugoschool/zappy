#include "Map.hpp"
#include "IRaylibEntities.hpp"
#include "Tile.hpp"
#include <utility>

zappy::Map::Map(int X, int Y) : _tiles(), _dimensions(std::pair(X, Y))
{
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            _tiles.insert({tileCoordinates(x, y), Tile(x, y, _dimensions)});
        }
    }
}


zappy::Map::~Map()
{}

zappy::Tile& zappy::Map::getTile(zappy::tileCoordinates coords)
{
    return _tiles.at(coords);
}

const std::pair<int, int> zappy::Map::getDimensions() const
{
    return _dimensions;
}

std::map<zappy::tileCoordinates, zappy::Tile> zappy::Map::getTiles() const
{
    return _tiles;
}

void zappy::Map::setDimensions(int width, int height)
{
    _dimensions = {width, height};
    _tiles.clear();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            _tiles.insert({tileCoordinates(x, y), Tile(x, y, _dimensions)});
        }
    }
}
