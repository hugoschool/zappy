#include "Zappy.hpp"
#include <string>

zappy::Zappy::Zappy(int port, std::string hostname) : _commuication(port, hostname),
    _graphical(), _exit(false), _communicationThread(&Zappy::LaunchSocket, this)
{
}

zappy::Zappy::~Zappy()
{
    _communicationThread.join();
}

void zappy::Zappy::Run()
{
}

void zappy::Zappy::LaunchSocket()
{
    _commuication.SocketLoop();
}
