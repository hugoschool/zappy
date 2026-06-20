#include "PlayerCommunication.hpp"
#include "SafeQueue.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

zappy::PlayerCommunication::PlayerCommunication(int port, std::string hostname, bool &exit, SafeQueue<std::string> &queue) : _communication(port, hostname),
    _safeQueue(queue), _exit(exit), _port(port), _hostname(hostname), _teamName()
{
}

zappy::PlayerCommunication::~PlayerCommunication()
{}

void zappy::PlayerCommunication::communicationLoop()
{
    _communication.sendMessage("team1\n");
    while (!_exit) {
        std::string message("");

        if (_safeQueue.tryPop(message)) {
            _communication.sendMessage(message);
        }
        std::string msg(_communication.runSocket(1));
        if (!msg.empty())
            std::cout << _communication.runSocket(1) << std::endl;
    }
}

void zappy::PlayerCommunication::parseMessages(std::string)
{
}
