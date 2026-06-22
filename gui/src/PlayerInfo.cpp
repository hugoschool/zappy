#include "APlayer.hpp"
#include "IEntity.hpp"
#include "IPlayer.hpp"
#include "Player.hpp"
#include "Utils.hpp"
#include <map>
#include <string>

zappy::PlayerInfo::PlayerInfo(int playerNb, tileCoordinates coord,
    int orientation, int level, std::string teamName) : APlayer( playerNb, coord, teamName, PlayerType::PLAYER),
    _orientation(orientation), _level(level), _teamName(teamName),
    _isIncantating(false), _inventory()
{
}

zappy::PlayerInfo::~PlayerInfo()
{}

int zappy::PlayerInfo::getOrientation()
{
    return _orientation;
}

bool zappy::PlayerInfo::isIncantating()
{
    return _isIncantating;
}

bool zappy::PlayerInfo::isMoving()
{
    return _moving;
}

void zappy::PlayerInfo::updatePos(zappy::tileCoordinates pos, int orientation)
{
    // if (_pos != pos) {
    //     _moving = true;
    //     _posVector.push_back(PositionHolder(_pos, pos, orientation));
    // }
    _displayPos = pos;
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

int zappy::PlayerInfo::getLevel()
{
    return _level;
}
