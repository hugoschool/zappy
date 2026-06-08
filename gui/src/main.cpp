#include "Exception.hpp"
#include "Map.hpp"
#include "Parser.hpp"
#include "Raylib.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    zappy::Parser parser;

    try {
        if (parser.parse(argc, argv) == zappy::HELP) {
            return 0;
        };
        zappy::Map map(10, 10);
        zappy::RaylibGraphical graphical(map);
        graphical.loop();
    } catch (zappy::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
