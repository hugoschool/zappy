#include "Map.hpp"
#include "ZappyBonus.hpp"
#include <iostream>
#include <string>

zappy::ZappyBonus::ZappyBonus(int port, std::string hostname) : _map(0, 0), _safeQueue(),
    _exit(false), _timeUnit(10), _protocol(port, hostname, _exit, _safeQueue, _timeUnit),
    _protocolThread(&zappy::ZappyBonus::launchProtocol, this)
{
}

zappy::ZappyBonus::~ZappyBonus()
{
    _protocolThread.join();
}

void zappy::ZappyBonus::loop()
{
    while (_exit == false) {
        std::vector<std::string> vec;
        _safeQueue.tryPop(vec);
        try {
            // _commands.at(vec.at(0))(vec);
        } catch (std::exception &) {
        }
        _exit = true;
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
