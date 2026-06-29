#include "Map.hpp"
#include "RaylibBonus.hpp"
#include "ZappyBonus.hpp"
#include <exception>
#include <iostream>
#include <queue>
#include <random>
#include <string>

zappy::ZappyBonus::ZappyBonus(int port, std::string hostname) : _map(0, 0), _geh(),
    _commandsQueue(4096), _sendQueue(4096), _playerMovesQueue(4096), _exit(false), _timeUnit(10), _id(getId()),
    _protocol(port, hostname, _exit, _commandsQueue, _sendQueue, _timeUnit),
    _protocolThread(&zappy::ZappyBonus::launchProtocol, this),
    _playerCommunication(port, hostname, _exit, _playerMovesQueue),
    _playerThread(&ZappyBonus::launchPlayerCommunication, this), _commands(),
    _teamsNames(), _graphical(_map, _geh, _id), _materialFactory(), _isPlayerLog(false), _ended(false), _winner()
{
    _commands.insert({"msz", std::bind(&zappy::ZappyBonus::msz, this, std::placeholders::_1)});
    _commands.insert({"bct", std::bind(&zappy::ZappyBonus::bct, this, std::placeholders::_1)});
    _commands.insert({"tna", std::bind(&zappy::ZappyBonus::tna, this, std::placeholders::_1)});
    _commands.insert({"pnw", std::bind(&zappy::ZappyBonus::pnw, this, std::placeholders::_1)});
    _commands.insert({"ppo", std::bind(&zappy::ZappyBonus::ppo, this, std::placeholders::_1)});
    _commands.insert({"plv", std::bind(&zappy::ZappyBonus::plv, this, std::placeholders::_1)});
    _commands.insert({"pin", std::bind(&zappy::ZappyBonus::pin, this, std::placeholders::_1)});
    _commands.insert({"pex", std::bind(&zappy::ZappyBonus::pex, this, std::placeholders::_1)});
    _commands.insert({"pbc", std::bind(&zappy::ZappyBonus::pbc, this, std::placeholders::_1)});
    _commands.insert({"pic", std::bind(&zappy::ZappyBonus::pic, this, std::placeholders::_1)});
    _commands.insert({"pie", std::bind(&zappy::ZappyBonus::pie, this, std::placeholders::_1)});
    _commands.insert({"pfk", std::bind(&zappy::ZappyBonus::pfk, this, std::placeholders::_1)});
    _commands.insert({"pdr", std::bind(&zappy::ZappyBonus::pdr, this, std::placeholders::_1)});
    _commands.insert({"pgt", std::bind(&zappy::ZappyBonus::pgt, this, std::placeholders::_1)});
    _commands.insert({"pdi", std::bind(&zappy::ZappyBonus::pdi, this, std::placeholders::_1)});
    _commands.insert({"enw", std::bind(&zappy::ZappyBonus::enw, this, std::placeholders::_1)});
    _commands.insert({"ebo", std::bind(&zappy::ZappyBonus::ebo, this, std::placeholders::_1)});
    _commands.insert({"edi", std::bind(&zappy::ZappyBonus::edi, this, std::placeholders::_1)});
    _commands.insert({"sgt", std::bind(&zappy::ZappyBonus::sgt, this, std::placeholders::_1)});
    _commands.insert({"sst", std::bind(&zappy::ZappyBonus::sst, this, std::placeholders::_1)});
    _commands.insert({"seg", std::bind(&zappy::ZappyBonus::seg, this, std::placeholders::_1)});
    _commands.insert({"smg", std::bind(&zappy::ZappyBonus::smg, this, std::placeholders::_1)});
    _commands.insert({"suc", std::bind(&zappy::ZappyBonus::suc, this, std::placeholders::_1)});
    _commands.insert({"sbp", std::bind(&zappy::ZappyBonus::sbp, this, std::placeholders::_1)});
}

zappy::ZappyBonus::~ZappyBonus()
{
    _protocolThread.join();
    _playerThread.join();
}

void zappy::ZappyBonus::loop()
{
    std::queue<std::string> queue;

    while (!_exit) {
        if (_commandsQueue.canRead()) {
            std::vector<std::string> vec = _commandsQueue.getElem();
            try {
                _commands.at(vec.at(0))(vec);
            } catch (std::exception &) {
            }
        }
        if (!_ended)
            _exit = _graphical.runScreens(_playerMovesQueue, _teamsNames);
        else
            _exit = _graphical.endScreen(_winner);
    }
}

void zappy::ZappyBonus::launchProtocol()
{
    try {
        _protocol.communicationLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void zappy::ZappyBonus::launchPlayerCommunication()
{
    try {
        _playerCommunication.communicationLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

int zappy::ZappyBonus::getId()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    return gen();
}
