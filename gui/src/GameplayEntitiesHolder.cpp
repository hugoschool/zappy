#include "Egg.hpp"
#include "GameplatEntitiesHolder.hpp"

zappy::GameplayEntitiesHolder::GameplayEntitiesHolder(): _players(), _dyingPlayers(), _broadcast()
{}

zappy::GameplayEntitiesHolder::~GameplayEntitiesHolder()
{}

void zappy::GameplayEntitiesHolder::addMessage(int id, std::string message)
{
    _broadcast.push(std::pair<int, std::string>(id, message));
}

std::pair<int, std::string> zappy::GameplayEntitiesHolder::popMessage()
{
    std::pair<int, std::string> message = _broadcast.front();
    _broadcast.pop();
    return message;
}

std::queue<std::pair<int, std::string>> zappy::GameplayEntitiesHolder::getBroadcast()
{
    return _broadcast;
}

void zappy::GameplayEntitiesHolder::addPlayer(int id, PlayerInfo playerInfo)
{
    _players.insert_or_assign(id, playerInfo);
}

zappy::PlayerInfo& zappy::GameplayEntitiesHolder::getPlayer(int id)
{
    return _players.at(id);
}

void zappy::GameplayEntitiesHolder::removePlayer(int id)
{
    _players.erase(id);
}

std::map<int, zappy::PlayerInfo>& zappy::GameplayEntitiesHolder::getPlayers()
{
    return _players;
}

void zappy::GameplayEntitiesHolder::addDyingPlayer(int id, PlayerInfo playerInfo)
{
    _dyingPlayers.insert_or_assign(id, playerInfo);
}

void zappy::GameplayEntitiesHolder::removeDyingPlayer(int id)
{
    _dyingPlayers.erase(id);
}

std::map<int, zappy::PlayerInfo>& zappy::GameplayEntitiesHolder::getDyingPlayers()
{
    return _dyingPlayers;
}

void zappy::GameplayEntitiesHolder::addEgg(int id, Egg egg)
{
    _eggs.insert_or_assign(id, egg);
}

zappy::Egg& zappy::GameplayEntitiesHolder::getEgg(int id)
{
    return _eggs.at(id);
}

void zappy::GameplayEntitiesHolder::removeEgg(int id)
{
    _eggs.erase(id);
}

std::map<int, zappy::Egg>& zappy::GameplayEntitiesHolder::getEggs()
{
    return _eggs;
}
