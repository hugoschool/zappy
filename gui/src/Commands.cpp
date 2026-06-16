#include "Egg.hpp"
#include "IEntity.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Zappy.hpp"
#include "entities/Food.hpp"
#include "entities/Materials.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <map>
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
            tile.addEntity(std::make_shared<Material>(static_cast<MaterialType>(i - 1), tileCoordinates(x, y), q[i]));
            index++;
        }
    } catch (std::exception &) {
    }
}

void zappy::Zappy::tna(std::vector<std::string> params)
{
    _teamsNames.push_back(params.at(1));
}

void zappy::Zappy::pnw(std::vector<std::string> params)
{
    int playerNb, x, y, orientation, level = 0;
    std::string teamName;

    try {
        std::string str = params.at(1);
        str.erase(str.begin());
        playerNb = std::stoi(str);
        x = std::stoi(params.at(2));
        y = std::stoi(params.at(3));
        orientation = std::stoi(params.at(4));
        level = std::stoi(params.at(5));
        teamName = params.at(6);

        try {
            PlayerInfo &player =  _geh.getPlayer(playerNb);
            player = PlayerInfo(playerNb, {x, y}, orientation, level, teamName);
        } catch (std::exception &) {
            _geh.addPlayer(playerNb, PlayerInfo(playerNb, {x, y},
                orientation, level, teamName));
        }
    } catch (std::exception &) {
    }
}

void zappy::Zappy::ppo(std::vector<std::string> params)
{
    int playerNb, x, y, orientation = 0;

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        playerNb = std::stoi(str);
        x = std::stoi(params.at(2));
        y = std::stoi(params.at(3));
        orientation = std::stoi(params.at(4));

        _geh.getPlayer(playerNb).updatePos({x, y}, orientation);
    } catch (std::exception &) {
    }
}

void zappy::Zappy::plv(std::vector<std::string> params)
{
    int playerNb, level = 0;

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        playerNb = std::stoi(str);
        level = std::stoi(params.at(2));

        _geh.getPlayer(playerNb).updateLevel(level);
    } catch (std::exception &) {
    }
}

void zappy::Zappy::pin(std::vector<std::string> params)
{
    int playerNb = 0;
    int q[7] = {0};
    std::vector<std::string> objets = {"food", "Linemate", "Deraumere",
        "Sibur", "Mendiane", "Phiras", "Thystame"};

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        playerNb = std::stoi(str);

        std::map<std::string, int>& inventory = _geh.getPlayer(playerNb).getInventory();

        for (int i = 0; i < 7; i++) {
            q[i] = std::stoi(params.at(i + 2));
        }
        int index = 0;
        for (auto objet : objets) {
            try {
                inventory.at(objet);
                inventory[objet] = q[index];
            } catch (std::exception &) {
                inventory.insert({objet, q[index]});
            }
            index++;
        }
    } catch (std::exception &) {
    }
}

void zappy::Zappy::pex(std::vector<std::string>)
{
    // Add to broadcast or animation
}

void zappy::Zappy::pbc(std::vector<std::string> params)
{
    std::string msg("");
    int playerNb = 0;

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        playerNb = std::stoi(str);

        for (size_t i = 2; i < params.size(); i++) {
            msg += params.at(i) + " ";
        }
        msg.erase(msg.length() - 1);
        _geh.addMessage(playerNb, msg);
    } catch (std::exception &) {
    }

}

void zappy::Zappy::pic(std::vector<std::string> params)
{
    try {
        std::string str;
        std::map<int , PlayerInfo> &players = _geh.getPlayers();
        for (size_t i = 3; i < params.size(); i++) {
            str = params.at(i);
            str.erase(str.begin());
            int playerNb = std::stoi(str);
            players.at(playerNb).setIncantation(true);
        }
    } catch (std::exception &) {
    }
}

void zappy::Zappy::pie(std::vector<std::string> params)
{
    int x, y = 0;
    bool result = false;

    try {
        x = std::stoi(params.at(1));
        y = std::stoi(params.at(2));
        result = std::stoi(params.at(3));
        for (auto &player : _geh.getPlayers()) {
            tileCoordinates pos = player.second.getCoords();
            if (pos == tileCoordinates(x, y)) {
                if (player.second.isIncantating()) {
                    player.second.setIncantation(false);
                    if (result)
                        player.second.updateLevel();
                }
            }
        }
    } catch (std::exception &) {
    }
}

void zappy::Zappy::pfk( std::vector<std::string> )
{
    //random à verifié plus tard
}

void zappy::Zappy::pdr(std::vector<std::string>)
{
    //TODO l'utiliser soit pour les animation soit pour le broadcast
}

void zappy::Zappy::pgt(std::vector<std::string>)
{
    //TODO l'utiliser soit pour les animation soit pour le broadcast
}

void zappy::Zappy::pdi(std::vector<std::string> params)
{
    int playerNb = 0;

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        playerNb = std::stoi(str);

        _geh.removePlayer(playerNb);
        // maybe add something to the broadcast
    } catch (std::exception &) {
    }
}

void zappy::Zappy::enw(std::vector<std::string> params)
{
    int eggNb, x, y = 0;

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        eggNb = std::stoi(str);

        x = std::stoi(params.at(3));
        y = std::stoi(params.at(4));
        _geh.addEgg(eggNb, Egg(eggNb, {x, y}, ""));
    } catch (std::exception &) {
    }
}

void zappy::Zappy::ebo(std::vector<std::string> params)
{
    int eggNb = 0;

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        eggNb = std::stoi(str);

        _geh.removeEgg(eggNb);
    } catch (std::exception &) {
    }
}

void zappy::Zappy::edi(std::vector<std::string> params)
{
    int eggNb = 0;

    try {
        std::string str(params.at(1));
        str.erase(str.begin());
        eggNb = std::stoi(str);

        _geh.removeEgg(eggNb);
    } catch (std::exception &) {
    }
}

void zappy::Zappy::sgt(std::vector<std::string> params)
{
    try {
        int time = std::stoi(params.at(1));
        _timeUnit = time;
    } catch (std::exception &) {
    }
}

void zappy::Zappy::sst(std::vector<std::string> params)
{
    // i'm not sure about this one
    try {
        int time = std::stoi(params.at(1));
        _timeUnit = time;
    } catch (std::exception &) {
    }
}

void zappy::Zappy::seg(std::vector<std::string> params)
{
    try {
        std::string msg(params.at(1));
        //TODO add to broadcast or event for the raylib
    } catch (std::exception &) {
    }
}

void zappy::Zappy::smg(std::vector<std::string> params)
{
    std::string msg("");

    try {
        for (size_t i = 2; i < params.size(); i++) {
            msg += params.at(i) + " ";
        }
        msg.erase(msg.length() - 1);
        _geh.addMessage(-1, msg);
    } catch (std::exception &) {
    }
}

void zappy::Zappy::suc(std::vector<std::string>)
{
    //does nothing ig
    std::cerr << "Unknown Command" << std::endl;
}

void zappy::Zappy::sbp(std::vector<std::string>)
{
    //same shit ig
    std::cerr << "Bad command parameter" << std::endl;
}
