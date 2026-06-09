#include "Communication.hpp"
#include "Exception.hpp"
#include <exception>
#include <functional>
#include <sstream>
#include <string>
#include <sys/poll.h>
#include <vector>

zappy::Communication::Communication(int port, std::string hostname) : _socket(port, hostname),
    _commands()
{
    _commands.insert({"msz", std::bind(&zappy::Communication::msz, this, std::placeholders::_1)});
    _commands.insert({"bct", std::bind(&zappy::Communication::bct, this, std::placeholders::_1)});
    _commands.insert({"tna", std::bind(&zappy::Communication::tna, this, std::placeholders::_1)});
    _commands.insert({"pnw", std::bind(&zappy::Communication::pnw, this, std::placeholders::_1)});
    _commands.insert({"ppo", std::bind(&zappy::Communication::ppo, this, std::placeholders::_1)});
    _commands.insert({"plv", std::bind(&zappy::Communication::plv, this, std::placeholders::_1)});
    _commands.insert({"pin", std::bind(&zappy::Communication::pin, this, std::placeholders::_1)});
    _commands.insert({"pex", std::bind(&zappy::Communication::pex, this, std::placeholders::_1)});
    _commands.insert({"pbc", std::bind(&zappy::Communication::pbc, this, std::placeholders::_1)});
    _commands.insert({"pic", std::bind(&zappy::Communication::pic, this, std::placeholders::_1)});
    _commands.insert({"pie", std::bind(&zappy::Communication::pie, this, std::placeholders::_1)});
    _commands.insert({"pfk", std::bind(&zappy::Communication::pfk, this, std::placeholders::_1)});
    _commands.insert({"pdr", std::bind(&zappy::Communication::pdr, this, std::placeholders::_1)});
    _commands.insert({"pgt", std::bind(&zappy::Communication::pgt, this, std::placeholders::_1)});
    _commands.insert({"pdi", std::bind(&zappy::Communication::pdi, this, std::placeholders::_1)});
    _commands.insert({"enw", std::bind(&zappy::Communication::enw, this, std::placeholders::_1)});
    _commands.insert({"ebo", std::bind(&zappy::Communication::ebo, this, std::placeholders::_1)});
    _commands.insert({"edi", std::bind(&zappy::Communication::edi, this, std::placeholders::_1)});
    _commands.insert({"sgt", std::bind(&zappy::Communication::sgt, this, std::placeholders::_1)});
    _commands.insert({"sst", std::bind(&zappy::Communication::sst, this, std::placeholders::_1)});
    _commands.insert({"seg", std::bind(&zappy::Communication::seg, this, std::placeholders::_1)});
    _commands.insert({"smg", std::bind(&zappy::Communication::smg, this, std::placeholders::_1)});
    _commands.insert({"suc", std::bind(&zappy::Communication::suc, this, std::placeholders::_1)});
    _commands.insert({"sbp", std::bind(&zappy::Communication::sbp, this, std::placeholders::_1)});
    _commands.insert({"WELCOME", std::bind(&zappy::Communication::welcome, this, std::placeholders::_1)});
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
    try {
        // std::cout << vec.at(0) << std::endl;
        _commands.at(vec.at(0))(vec);
    } catch (std::exception &) {
    }
}


