#include "Parser.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include <cstdlib>

zappy::Parser::Parser() {}

zappy::Parser::~Parser() {}

void zappy::Parser::printHelp()
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
}

void zappy::Parser::parse(int argc, char **argv)
{
    if (argc != 3) {
        throw ParserException("Wrong argument number.");
    }

    if (static_cast<std::string>(argv[1]) == "--help") {
        printHelp();
        return;
    }

    if (Utils:: isInt(argv[1]) == false) {
        throw ParserException("Invalid port.");
    }
    _port = std::atoi(argv[1]);

    _hostname = static_cast<std::string>(argv[2]);
}

std::pair<int, std::string> zappy::Parser::getArgs()
{
    return (std::pair<int, std::string>(_port, _hostname));
}
