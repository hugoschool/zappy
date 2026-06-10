#include "Exception.hpp"
#include "Parser.hpp"
#include "Zappy.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    zappy::Parser parser;

    try {
        if (parser.parse(argc, argv) == zappy::HELP) {
            return 0;
        };
        zappy::Zappy zap(parser.getArgs().first, parser.getArgs().second);
        zap.loop();
    } catch (zappy::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
