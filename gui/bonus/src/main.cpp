#include "Exception.hpp"
#include "Parser.hpp"
#include "ZappyBonus.hpp"

int main(int argc, char **argv)
{
    zappy::Parser parser;

    try {
        if (parser.parse(argc, argv) == zappy::HELP) {
            return 0;
        }
        zappy::ZappyBonus zap(parser.getArgs().first, parser.getArgs().second);
        zap.loop();
    } catch (zappy::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
