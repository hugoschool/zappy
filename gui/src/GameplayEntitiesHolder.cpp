#include "GameplatEntitiesHolder.hpp"

zappy::GameplayEntitiesHolder::GameplayEntitiesHolder(): _players(), _broadcast()
{}

zappy::GameplayEntitiesHolder::~GameplayEntitiesHolder()
{}

void zappy::GameplayEntitiesHolder::addMessage(int id, std::string message)
{
    _broadcast.push(std::pair<int, std::string>(id, message));
}

void zappy::GameplayEntitiesHolder::popMessage()
{
    _broadcast.pop();
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
