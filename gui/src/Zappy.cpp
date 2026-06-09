#include "Zappy.hpp"
#include "Raylib.hpp"
#include <memory>
#include <string>

zappy::Zappy::Zappy(int port, std::string hostname) : _map(0, 0), _exit(false), _commuication(port, hostname, _map, _exit),
    _graphical(std::make_unique<zappy::RaylibGraphical>(_map)), _communicationThread(&Zappy::LaunchSocket, this)
{
}

zappy::Zappy::~Zappy()
{
    _communicationThread.join();
}

void zappy::Zappy::Run()
{
    _graphical->loop();
    _exit = true;
}

void zappy::Zappy::LaunchSocket()
{
    _commuication.SocketLoop();
}
