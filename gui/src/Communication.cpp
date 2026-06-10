#include "Communication.hpp"
#include "Exception.hpp"
#include "SafeQueue.hpp"
#include <sstream>
#include <string>
#include <sys/poll.h>
#include <vector>

zappy::Communication::Communication(int port, std::string hostname, bool &exit, SafeQueue<std::vector<std::string>> &queue) : _socket(port, hostname),
    _exit(exit), _safeQueue(queue)
{
    _socket.Send("GRAPHIC\n");
}

zappy::Communication::~Communication()
{
}

void zappy::Communication::SocketLoop()
{
    while (true) {
        if (_exit)
            break;
        if (_socket.Poll() < 0)
            throw zappy::Exception("Poll: error");
        for (int i = 0; i < 1; i++) {
            UpdateFd(i);
        }
    }
}

void zappy::Communication::UpdateFd(int i)
{
    if (_socket._pfds[i].revents & POLLIN) {
        ReadMessage();
    } else if (_socket._pfds[i].revents & POLLHUP || _socket._pfds[i].revents & POLLERR) {
        _socket.Close();
    }
}

void zappy::Communication::ReadMessage()
{
    std::string msg = _socket.Receive();
    std::stringstream ss(msg);
    char del = '\n';
    std::string line;

    while (std::getline(ss, line, del)) {
        ParseMessage(line);
    }
}

void zappy::Communication::ParseMessage(std::string msg)
{
    std::string line;
    std::stringstream ss(msg);
    std::vector<std::string> vec;

    while (ss >> line) {
        vec.push_back(line);
    }
    _safeQueue.push(vec);
}


