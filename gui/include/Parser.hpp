#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <utility>
namespace zappy {
    constexpr int HELP = 1;
    class Parser {
        private:
            int _port;
            std::string _hostname;
        public:
            Parser();
            ~Parser();

            int parse(int argc, char **argv);
            std::pair<int, std::string> getArgs();
            void printHelp();

            void parseArg(char **argv, int index);
    };
}
