#include "APlayer.hpp"
#include "IEntity.hpp"
#include "IPlayer.hpp"
#include <string>


zappy::APlayer::APlayer(int id, zappy::tileCoordinates pos, std::string teamName, PlayerType type) :
    _pos(pos), _displayPos(pos), _teamName(teamName), _type(type), _id(id), _selected(false)
{
}

zappy::APlayer::~APlayer()
{}

zappy::tileCoordinates zappy::APlayer::getPos()
{
    return _pos;
}

std::string zappy::APlayer::getTeamName()
{
    return _teamName;
}

zappy::tileCoordinates zappy::APlayer::getCoords()
{
    return _pos;
}

zappy::floatCoordinates zappy::APlayer::getDisplayCoords()
{
    return _displayPos;
}

void zappy::APlayer::updatePos(zappy::tileCoordinates pos, int)
{
    _pos = pos;
}

zappy::PlayerType zappy::APlayer::getType()
{
    return _type;
}

int zappy::APlayer::getId()
{
    return _id;
}

bool zappy::APlayer::getSelected()
{
    return _selected;
}

void zappy::APlayer::setSelected(bool selected)
{
    _selected = selected;
}
