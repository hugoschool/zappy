#include "Zappy.hpp"
#include <string>

zappy::Zappy::Zappy(int port, std::string hostname) : _commuication(port, hostname),
    _graphical(), _exit(false)
{
}

zappy::Zappy::~Zappy()
{}

void zappy::Zappy::Run()
{

}

void zappy::Zappy::SocketLoop()
{
}
