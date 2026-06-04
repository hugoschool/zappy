#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <utility>
namespace zappy {
    class Parser {
        private:
            int _port;
            std::string _hostname;
        public:
            Parser();
            ~Parser();

            void parse(int argc, char **argv);
            std::pair<int, std::string> getArgs();
            void printHelp();

            void parseArg(char **argv, int index);
    };
}
