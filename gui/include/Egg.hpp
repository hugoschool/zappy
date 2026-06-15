#pragma once

#include "APlayer.hpp"
#include "IEntity.hpp"
#include "IPlayer.hpp"
namespace zappy {
    class Egg : public APlayer {
        public:
            Egg() = delete;
            Egg(int, tileCoordinates, std::string);
            ~Egg();

        private:
            tileCoordinates _pos;
            std::string _teamName;
            PlayerType _type;
            int _id;
    };
}
