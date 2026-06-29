#include "entities/Food.hpp"
#include "IEntity.hpp"
#include "IModelHolder.hpp"
#include "RaylibModelHolder.hpp"
#include "entities/AEntity.hpp"
#include "Raylib.hpp"

zappy::Food::Food(zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount)
{}

zappy::Food::~Food()
{}
