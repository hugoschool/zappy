#include "Parser.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include <cstdlib>

zappy::Parser::Parser()
{
    _hostname = "fakehostname";
    _port = -67;
}

zappy::Parser::~Parser() {}

void zappy::Parser::printHelp()
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
}

void zappy::Parser::parseArg(char **argv, int index)
{
    if (argv[index + 1] == NULL)
        return;
    std::string argIndex = static_cast<std::string>(argv[index]);

    if (argIndex == "-p") {
        if (Utils::isOfType<int>(argv[index + 1]) == false) {
            throw ParserException("Invalid port.");
        }
        _port = std::atoi(argv[index + 1]);
    }
    if (argIndex == "-h") {
        _hostname = static_cast<std::string>(argv[index + 1]);
    }
}

int zappy::Parser::parse(int argc, char **argv)
{
    if (argc == 2 && static_cast<std::string>(argv[1]) == "--help") {
        printHelp();
        return HELP;
    }

    if (argc != 5) {
        throw ParserException("Wrong argument number.");
    }

    for (int i = 0; argv[i] != NULL; i++) {
        parseArg(argv, i);
    }

    if (_port == -67 || _hostname == "fakehostname") {
        throw ParserException("Args are not correct.");
    }
    return 0;
}

std::pair<int, std::string> zappy::Parser::getArgs()
{
    return (std::pair<int, std::string>(_port, _hostname));
}
