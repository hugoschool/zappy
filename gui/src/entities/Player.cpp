#include "entities/Player.hpp"
#include "IEntity.hpp"
#include "entities/AEntity.hpp"

zappy::Player::Player(zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount)
{}

zappy::Player::~Player()
{}

void zappy::Player::draw(zappy::ModelHolder& modelHolder, std::pair<int, int> dimensions)
{
    float heightVal = 0.05;
    for (int i = 0; i < _amount; i++) {
        modelHolder.getPlayerModel().Draw(Vector3(_coords.first - (dimensions.first / 2.0f) - 0.2, heightVal, _coords.second - (dimensions.second / 2.0f)), 2.0f, raylib::Color::Gold());
        heightVal += 0.15;
    }
}
