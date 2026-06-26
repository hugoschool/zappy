#include "Zappy.hpp"
#include "Raylib.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

zappy::Zappy::Zappy(int port, std::string hostname) : _map(0, 0), _geh(), _recvBuffer(4092), _exit(false), _timeUnit(10), _protocol(port, hostname, _exit, _recvBuffer, _recvBuffer, _timeUnit),
    _graphical(std::make_unique<zappy::RaylibGraphical>(_map, _geh)), _protocolThread(&Zappy::launchProtocol, this), _commands()
{
    _commands.insert({"msz", std::bind(&zappy::Zappy::msz, this, std::placeholders::_1)});
    _commands.insert({"bct", std::bind(&zappy::Zappy::bct, this, std::placeholders::_1)});
    _commands.insert({"tna", std::bind(&zappy::Zappy::tna, this, std::placeholders::_1)});
    _commands.insert({"pnw", std::bind(&zappy::Zappy::pnw, this, std::placeholders::_1)});
    _commands.insert({"ppo", std::bind(&zappy::Zappy::ppo, this, std::placeholders::_1)});
    _commands.insert({"plv", std::bind(&zappy::Zappy::plv, this, std::placeholders::_1)});
    _commands.insert({"pin", std::bind(&zappy::Zappy::pin, this, std::placeholders::_1)});
    _commands.insert({"pex", std::bind(&zappy::Zappy::pex, this, std::placeholders::_1)});
    _commands.insert({"pbc", std::bind(&zappy::Zappy::pbc, this, std::placeholders::_1)});
    _commands.insert({"pic", std::bind(&zappy::Zappy::pic, this, std::placeholders::_1)});
    _commands.insert({"pie", std::bind(&zappy::Zappy::pie, this, std::placeholders::_1)});
    _commands.insert({"pfk", std::bind(&zappy::Zappy::pfk, this, std::placeholders::_1)});
    _commands.insert({"pdr", std::bind(&zappy::Zappy::pdr, this, std::placeholders::_1)});
    _commands.insert({"pgt", std::bind(&zappy::Zappy::pgt, this, std::placeholders::_1)});
    _commands.insert({"pdi", std::bind(&zappy::Zappy::pdi, this, std::placeholders::_1)});
    _commands.insert({"enw", std::bind(&zappy::Zappy::enw, this, std::placeholders::_1)});
    _commands.insert({"ebo", std::bind(&zappy::Zappy::ebo, this, std::placeholders::_1)});
    _commands.insert({"edi", std::bind(&zappy::Zappy::edi, this, std::placeholders::_1)});
    _commands.insert({"sgt", std::bind(&zappy::Zappy::sgt, this, std::placeholders::_1)});
    _commands.insert({"sst", std::bind(&zappy::Zappy::sst, this, std::placeholders::_1)});
    _commands.insert({"seg", std::bind(&zappy::Zappy::seg, this, std::placeholders::_1)});
    _commands.insert({"smg", std::bind(&zappy::Zappy::smg, this, std::placeholders::_1)});
    _commands.insert({"suc", std::bind(&zappy::Zappy::suc, this, std::placeholders::_1)});
    _commands.insert({"sbp", std::bind(&zappy::Zappy::sbp, this, std::placeholders::_1)});
}

zappy::Zappy::~Zappy()
{
    _protocolThread.join();
}

void zappy::Zappy::loop()
{
    while (_exit == false) {
        if (_recvBuffer.canRead()) {
            std::vector<std::string> vec = _recvBuffer.getElem();
            try {
                _commands.at(vec.at(0))(vec);
            } catch (std::exception &) {
            }
        }
        _exit = _graphical->run();
    }
}

void zappy::Zappy::launchProtocol()
{
    try {
        _protocol.communicationLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
