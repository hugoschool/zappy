#include "Zappy.hpp"
#include <exception>
#include <string>
#include <vector>

void zappy::Zappy::msz(std::vector<std::string> params)
{
    try {
        int x = std::stoi(params.at(1));
        int y = std::stoi(params.at(2));
        _map.setDimensions(x, y);
    } catch (std::exception &) {
    }
}

void zappy::Zappy::bct( std::vector<std::string> )
{}

void zappy::Zappy::tna( std::vector<std::string> )
{}

void zappy::Zappy::pnw( std::vector<std::string> )
{}

void zappy::Zappy::ppo( std::vector<std::string> )
{}

void zappy::Zappy::plv( std::vector<std::string> )
{}

void zappy::Zappy::pin( std::vector<std::string> )
{}

void zappy::Zappy::pex( std::vector<std::string> )
{}

void zappy::Zappy::pbc( std::vector<std::string> )
{}

void zappy::Zappy::pic( std::vector<std::string> )
{}

void zappy::Zappy::pie( std::vector<std::string> )
{}

void zappy::Zappy::pfk( std::vector<std::string> )
{}

void zappy::Zappy::pdr( std::vector<std::string> )
{}

void zappy::Zappy::pgt( std::vector<std::string> )
{}

void zappy::Zappy::pdi( std::vector<std::string> )
{}

void zappy::Zappy::enw( std::vector<std::string> )
{}

void zappy::Zappy::ebo( std::vector<std::string> )
{}

void zappy::Zappy::edi( std::vector<std::string> )
{}

void zappy::Zappy::sgt( std::vector<std::string> )
{}

void zappy::Zappy::sst( std::vector<std::string> )
{}

void zappy::Zappy::seg( std::vector<std::string> )
{}

void zappy::Zappy::smg( std::vector<std::string> )
{}

void zappy::Zappy::suc( std::vector<std::string> )
{}

void zappy::Zappy::sbp( std::vector<std::string> )
{}
