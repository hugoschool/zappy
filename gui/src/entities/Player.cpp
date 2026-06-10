#include "entities/Player.hpp"
#include "IEntity.hpp"
#include "entities/AEntity.hpp"

zappy::Player::Player(zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount)
{}

zappy::Player::~Player()
{}

void zappy::Player::draw(zappy::ModelHolder& modelHolder)
{
    static_cast<void>(modelHolder);
    return;
}
