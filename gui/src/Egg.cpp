#include "Egg.hpp"
#include "APlayer.hpp"
#include "IEntity.hpp"
#include "IPlayer.hpp"
#include <string>

zappy::Egg::Egg(int id, zappy::tileCoordinates pos, std::string teamName) : APlayer(id, pos, teamName, EGG)
{
}

zappy::Egg::~Egg()
{
}
