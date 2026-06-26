#include "APlayer.hpp"
#include "IRaylibEntities.hpp"
#include "IPlayer.hpp"
#include "Player.hpp"
#include "Utils.hpp"
#include <map>
#include <string>

zappy::PlayerInfo::PlayerInfo(int playerNb, tileCoordinates coord,
    int orientation, int level, std::string teamName) : APlayer( playerNb, coord, teamName, PlayerType::PLAYER),
    _orientation(orientation), _level(level), _teamName(teamName),
    _isIncantating(false), _moving(false), _taking(false), _dropping(false), _hitting(false), _inventory()
{
}

zappy::PlayerInfo::~PlayerInfo()
{}

int zappy::PlayerInfo::getOrientation()
{
    return _orientation;
}

bool zappy::PlayerInfo::isIncantating() const
{
    return _isIncantating;
}

bool zappy::PlayerInfo::isMoving() const
{
    return _moving;
}

bool zappy::PlayerInfo::isDropping() const
{
    return _dropping;
}

bool zappy::PlayerInfo::isTaking() const
{
    return _taking;
}

bool zappy::PlayerInfo::isHitting() const
{
    return _hitting;
}

void zappy::PlayerInfo::updatePos(zappy::tileCoordinates pos, int orientation)
{
    if (_pos != pos) {
        _moving = true;
        _posVector.push_back(PositionHolder(_pos, pos, orientation));
    }
    _pos = pos;
    _orientation = orientation;
}

void zappy::PlayerInfo::updateDisplayPos()
{
    if (_posVector.empty()) {
        _moving = false;
        return;
    }
    PositionHolder &posHolder = _posVector.front();

    if (zappy::Utils::floatCoordsCompare(_displayPos, posHolder._posToReach, posHolder._iterationAddedValue)) {
        _displayPos = posHolder._posToReach;
        _posVector.erase(_posVector.begin());
        if (_posVector.empty())
            return;
        else {
            posHolder = _posVector.front();
        }
    }
    _orientation = posHolder._orientataion;
    _displayPos.first += posHolder._iterationAddedValue.first;
    _displayPos.second += posHolder._iterationAddedValue.second;
}

void zappy::PlayerInfo::updateLevel()
{
    _level++;
}

void zappy::PlayerInfo::updateLevel(int level)
{
    _level = level;
}

std::map<std::string, int>& zappy::PlayerInfo::getInventory()
{
    return _inventory;
}

void zappy::PlayerInfo::setIncantation(bool value)
{
    _isIncantating = value;
}

void zappy::PlayerInfo::setDropping(bool value)
{
    _dropping = value;
}

void zappy::PlayerInfo::setTaking(bool value)
{
    _taking = value;
}

void zappy::PlayerInfo::setHitting(bool value)
{
    _hitting = value;
}

int zappy::PlayerInfo::getLevel()
{
    return _level;
}
