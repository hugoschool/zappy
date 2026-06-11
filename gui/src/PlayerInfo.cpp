#include "IEntity.hpp"
#include "Player.hpp"
#include <string>

zappy::PlayerInfo::PlayerInfo(int playerNb, tileCoordinates coord,
    int orientation, int level, std::string teamName) : _playerNb(playerNb),
    _pos(coord), _orientation(orientation), _level(level), _teamName(teamName),
    _inventory(), _isEgg(false)
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

bool zappy::PlayerInfo::isEgg()
{
    return _isEgg;
}

void zappy::PlayerInfo::updatePos(zappy::tileCoordinates pos, int orientation)
{
    _pos = pos;
    _orientation = orientation;
}

void zappy::PlayerInfo  ::updateLevel(int newLevel)
{
    _level = newLevel;
}
