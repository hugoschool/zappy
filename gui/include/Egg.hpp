#pragma once

#include "APlayer.hpp"
#include "IEntity.hpp"
namespace zappy {
    class Egg : public APlayer {
        public:
            Egg() = delete;
            Egg(int, tileCoordinates, std::string);
            ~Egg();
    };
}
