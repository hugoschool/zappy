#include "PlayerCommunication.hpp"
#include "CircularBuffer.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>

zappy::PlayerCommunication::PlayerCommunication(int port, std::string hostname, bool &exit, CircularBuffer<std::string> &queue) : _communication(port, hostname),
    _circularBuffer(queue), _exit(exit), _port(port), _hostname(hostname), _teamName()
{
}

zappy::PlayerCommunication::~PlayerCommunication()
{
}

void zappy::PlayerCommunication::communicationLoop()
{
    while (!_exit) {
        std::string message("");
        std::string msg;

        if (_circularBuffer.canRead()) {
            message = _circularBuffer.getElem();
            try {
                _communication.sendMessage(message);
            } catch (std::exception &) {
                break;
            }
        }
        try {
            msg = _communication.runSocket(1);
        } catch (std::exception &) {
            break;
        }
        if (msg == "dead" || msg == "dead\n")
            break;
        if (!msg.empty())
            std::cout << msg << std::endl;
    }
}

void zappy::PlayerCommunication::parseMessages(std::string)
{
}
