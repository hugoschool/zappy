#include "Utils.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>

bool zappy::Utils::isInt(std::string str)
{
    for (char c: str) {
        if (std::isdigit(c) == false) {
            return false;
        }
    }
    return true;
}

bool zappy::Utils::isSize_t(std::string str)
{
    if (isInt(str) == false) {
        return false;
    }

    long long nb = std::atoll(str.c_str());

    if (nb < 0) {
        return false;
    } else {
        return true;
    }
}

bool zappy::Utils::isFloat(std::string str)
{
    std::size_t dotCounter = 0;

    for (char c: str) {
        if (c == '.') {
            dotCounter += 1;
            if (dotCounter > 1) {
                return false;
            }
        } else if (std::isdigit(c) == false) {
            return false;
        }
    }
    return true;
}
