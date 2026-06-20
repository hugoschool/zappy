#include "PlayerCommunication.hpp"
#include "SafeQueue.hpp"
#include <string>

zappy::PlayerCommunication::PlayerCommunication(int port, std::string hostname, bool &exit, SafeQueue<std::string> &queue) : _communication(port, hostname),
    _safeQueue(queue), _exit(exit), _port(port), _hostname(hostname), _teamName()
{
    _communication.sendMessage("team1");
}

zappy::PlayerCommunication::~PlayerCommunication()
{}

void zappy::PlayerCommunication::communicationLoop()
{
    while (!_exit) {
        std::string message("");

        if (_safeQueue.tryPop(message)) {
            _communication.sendMessage(message);
        }
    }
}

void zappy::PlayerCommunication::parseMessages(std::string)
{
}
