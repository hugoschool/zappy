#include "IEntity.hpp"
#include "Tile.hpp"
#include "Zappy.hpp"
#include "entities/Food.hpp"
#include "entities/Materials.hpp"
#include <exception>
#include <memory>
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

void zappy::Zappy::bct(std::vector<std::string> params)
{
    int x, y = 0;
    int q[7] = {0};

    try {
        x = std::stoi(params.at(1));
        y = std::stoi(params.at(2));
        int index = 4;
        Tile &tile = _map.getTile({x, y});
        tile.clear();
        q[0] = std::stoi(params.at(3));
        tile.addEntity(std::make_shared<Food>(tileCoordinates(x, y), q[0]));
        for (int i = 1; i < 7; i++) {
            q[i] = std::stoi(params.at(index));
            if (q[i] != 0) {
                tile.addEntity(std::make_shared<Material>(static_cast<MaterialType>(i - 1), tileCoordinates(x, y), q[i]));
            }
            index++;
        }
    } catch (std::exception &) {
    }
}

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
