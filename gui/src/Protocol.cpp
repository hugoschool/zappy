#include "Protocol.hpp"
#include <exception>
#include <sstream>
#include <string>
#include <vector>

zappy::Protocol::Protocol(int port, std::string hostname, bool &exit, CircularBuffer<std::vector<std::string>> &send,
    CircularBuffer<std::vector<std::string>> &recv, int &time) :
    _sendBuffer(send), _receiveBuffer(recv), _communication(port, hostname), _exit(exit), _timeUnit(time)
{
    _communication.sendMessage("GRAPHIC\n");
}

zappy::Protocol::~Protocol()
{}

void zappy::Protocol::communicationLoop()
{
    while (!_exit) {
        std::string msg("");
        try {
            msg = _communication.runSocket(_timeUnit);
        } catch (std::exception &) {
            break;
        }
        parseMessages(msg);
        while (_receiveBuffer.canRead()) {
            _communication.sendMessage(_receiveBuffer.getElem().at(0));
        }
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
    _sendBuffer.addElement(vec);
}
