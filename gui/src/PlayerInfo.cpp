#include "APlayer.hpp"
#include "IEntity.hpp"
#include "IPlayer.hpp"
#include "Player.hpp"
#include <map>
#include <string>

zappy::PlayerInfo::PlayerInfo(int playerNb, tileCoordinates coord,
    int orientation, int level, std::string teamName) : APlayer( playerNb, coord, teamName, PlayerType::PLAYER), _playerNb(playerNb),
    _pos(coord), _orientation(orientation), _level(level), _teamName(teamName),
    _inventory()
{
}

zappy::PlayerInfo::~PlayerInfo()
{}

std::string zappy::PlayerInfo::getTeamName()
{
    return _teamName;
}

void zappy::PlayerInfo::updatePos(zappy::tileCoordinates pos, int orientation)
{
    _pos = pos;
    _orientation = orientation;
}

void zappy::PlayerInfo::updateLevel(int newLevel)
{
    _level = newLevel;
}

std::map<std::string, int>& zappy::PlayerInfo::getInventory()
{
    return _inventory;
}
