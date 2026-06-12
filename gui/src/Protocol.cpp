#include "Protocol.hpp"
#include "SafeQueue.hpp"
#include <sstream>
#include <string>

zappy::Protocol::Protocol(int port, std::string hostname, bool &exit, SafeQueue<std::vector<std::string>> &queue) :
    _safeQueue(queue), _communication(port, hostname), _exit(exit)
{
    _communication.sendMessage("GRAPHIC\n");
}

zappy::Protocol::~Protocol()
{}

void zappy::Protocol::communicationLoop()
{
    while (!_exit) {
        std::string msg = _communication.runSocket();
        parseMessages(msg);
    }
}

void zappy::Protocol::parseMessages(std::string msg)
{
    std::string line;
    std::stringstream ss(msg);
    char delim = '\n';

    while (std::getline(ss, line, delim)) {
        sendCommand(line);
    }
}

void zappy::Protocol::sendCommand(std::string command)
{
    std::string line;
    std::stringstream ss(command);
    std::vector<std::string> vec;

    while (ss >> line) {
        vec.push_back(line);
    }
    _safeQueue.push(vec);
}
