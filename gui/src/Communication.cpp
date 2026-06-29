#include "Communication.hpp"
#include "Exception.hpp"
#include "INetwork.hpp"
#include "Socket.hpp"
#include <memory>
#include <string>
#include <sys/poll.h>

zappy::Communication::Communication(int port, std::string hostname) : _socket(std::make_unique<Socket>(port, hostname))
{
}

zappy::Communication::~Communication()
{
}

std::string zappy::Communication::runSocket(int timeout)
{
    std::string msg("");
    if (_socket->pollConnections(timeout) < 0)
        throw zappy::Exception("Poll: error");
    msg = checkFd();
    return msg;
}

std::string zappy::Communication::checkFd()
{
    stateFd value = _socket->updateFd();
    if (value == stateFd::READY) {
        return readMessage();
    } else if (value == stateFd::CLOSE) {
        _socket->closeSocket();
        throw zappy::Exception("Socket closed");
    }
    return std::string("");
}

std::string zappy::Communication::readMessage()
{
    return _socket->receive();
}

void zappy::Communication::sendMessage(std::string msg)
{
    _socket->sendMsg(msg);
}
