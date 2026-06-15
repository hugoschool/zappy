#include "APlayer.hpp"
#include "IEntity.hpp"
#include "IPlayer.hpp"
#include "Player.hpp"
#include <iostream>
#include <map>
#include <string>

zappy::PlayerInfo::PlayerInfo(int playerNb, tileCoordinates coord,
    int orientation, int level, std::string teamName) : APlayer( playerNb, coord, teamName, PlayerType::PLAYER), _playerNb(playerNb),
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
    _moving = true;
    _posVector.push_back(PositionHolder(_pos, pos, orientation));
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

    if (_displayPos == posHolder._posToReach) {
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

void zappy::PlayerInfo::updateLevel(int newLevel)
{
    _level = newLevel;
}

std::map<std::string, int>& zappy::PlayerInfo::getInventory()
{
    return _inventory;
}
