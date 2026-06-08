#include "Communication.hpp"
#include "Exception.hpp"
#include <functional>
#include <sstream>
#include <string>
#include <sys/poll.h>
#include <vector>

zappy::Communication::Communication(int port, std::string hostname) : _socket(port, hostname),
    _commands()
{
    _commands.insert({"msz", zappy::Communication::msz});
    _commands.insert({"bct", zappy::Communication::bct});
    _commands.insert({"tna", zappy::Communication::tna});
    _commands.insert({"pnw", zappy::Communication::pnw});
    _commands.insert({"ppo", zappy::Communication::ppo});
    _commands.insert({"plv", zappy::Communication::plv});
    _commands.insert({"pin", zappy::Communication::pin});
    _commands.insert({"pex", zappy::Communication::pex});
    _commands.insert({"pbc", zappy::Communication::pbc});
    _commands.insert({"pic", zappy::Communication::pic});
    _commands.insert({"pie", zappy::Communication::pie});
    _commands.insert({"pfk", zappy::Communication::pfk});
    _commands.insert({"pdr", zappy::Communication::pdr});
    _commands.insert({"pdi", zappy::Communication::pdi});
    _commands.insert({"enw", zappy::Communication::enw});
    _commands.insert({"ebo", zappy::Communication::ebo});
    _commands.insert({"edi", zappy::Communication::edi});
    _commands.insert({"sgt", zappy::Communication::sgt});
    _commands.insert({"sst", zappy::Communication::sst});
    _commands.insert({"seg", zappy::Communication::seg});
    _commands.insert({"smg", zappy::Communication::smg});
    _commands.insert({"suc", zappy::Communication::suc});
    _commands.insert({"sbp", zappy::Communication::sbp});
}

zappy::Communication::~Communication()
{
}

void zappy::Communication::SocketLoop()
{
    while (true) {
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
    _commands.at(vec.at(0))(this, vec);
}


