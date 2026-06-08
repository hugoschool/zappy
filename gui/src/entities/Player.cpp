#include "entities/Player.hpp"
#include "IEntity.hpp"
#include "entities/AEntity.hpp"
zappy::Player::Player(): AEntity()
{}

zappy::Player::Player(zappy::tileCoordinates coords): AEntity(coords)
{}

zappy::Player::~Player()
{}

void zappy::Player::draw()
{
    return;
}
