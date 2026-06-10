#include "Communication.hpp"
#include "Exception.hpp"
#include <string>
#include <sys/poll.h>

zappy::Communication::Communication(int port, std::string hostname) : _socket(port, hostname)
{
}

zappy::Communication::~Communication()
{
}

std::string zappy::Communication::runSocket()
{
    std::string msg("");
    if (_socket.Poll() < 0)
        throw zappy::Exception("Poll: error");
    for (int i = 0; i < 1; i++) {
        msg += UpdateFd(i);
    }
    return msg;
}

std::string zappy::Communication::UpdateFd(int i)
{
    if (_socket._pfds[i].revents & POLLIN) {
        return ReadMessage();
    } else if (_socket._pfds[i].revents & POLLHUP || _socket._pfds[i].revents & POLLERR) {
        _socket.Close();
    }
    return std::string("");
}

std::string zappy::Communication::ReadMessage()
{
    return _socket.Receive();
}

void zappy::Communication::sendMessage(std::string msg)
{
    _socket.Send(msg);
}
