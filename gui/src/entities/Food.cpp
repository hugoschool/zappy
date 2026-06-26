#include "entities/Food.hpp"
#include "IRaylibEntities.hpp"
#include "RaylibModelHolder.hpp"
#include "entities/AEntity.hpp"
#include "Raylib.hpp"

zappy::Food::Food(zappy::tileCoordinates coords, int amount): zappy::AEntity(coords, amount)
{}

zappy::Food::~Food()
{}

void zappy::Food::draw(zappy::RaylibModelHolder& RaylibModelHolder, std::pair<int, int> dimensions)
{
    if (_amount == 0)
        return;
    int amount = _amount;
    if (amount > 20)
        amount = 20;
    float heightVal = 0.05;
    for (int i = 0; i < amount; i++) {
        RaylibModelHolder.getFoodModel().Draw(Vector3(_coords.first - (dimensions.first / 2.0f) - 0.2 + 0.5f, heightVal, _coords.second - (dimensions.second / 2.0f) + 0.5f), 1.0f);
        heightVal += 0.05;
    }
}

void zappy::Food::drawLowObject(std::pair<int, int> dimensions)
{
    std::string str = std::to_string(_amount);
    raylib::DrawText(str.c_str(), (_coords.first * 20 + 1) / (dimensions.first / 42.0f), (_coords.second * 20 + 1) / (dimensions.second / 42.0f), 10, raylib::Color::Brown());
}
