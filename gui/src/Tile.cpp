#include "Tile.hpp"

zappy::Tile::Tile() : _coords(0, 0), _entities()
{
}

zappy::Tile::Tile(int X, int Y) : _coords(X, Y), _entities()
{
}

zappy::Tile::~Tile()
{
}
