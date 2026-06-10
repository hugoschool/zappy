#pragma once

#include "IEntity.hpp"
#include <string>
namespace zappy {
    typedef struct {
        int playerNb;
        tileCoordinates pos;
        int orientation;
        int level;
        std::string teamName;
    } PlayerInfo;
}
