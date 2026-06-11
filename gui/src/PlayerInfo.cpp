#include "IEntity.hpp"
#include "Player.hpp"
#include <string>

zappy::PlayerInfo::PlayerInfo(int playerNb, tileCoordinates coord,
    int orientation, int level, std::string teamName) : _playerNb(playerNb),
    _pos(coord), _orientation(orientation), _level(level), _teamName(teamName),
    _inventory()
{}

zappy::PlayerInfo::~PlayerInfo()
{}

zappy::tileCoordinates zappy::PlayerInfo::getCoords()
{
    return _pos;
}

std::string zappy::PlayerInfo::getTeamName()
{
    return _teamName;
}
