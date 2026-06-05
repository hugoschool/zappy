#pragma once

#include "IEntity.hpp"
#include "Tiles.hpp"
#include <map>

namespace zappy {
    class Map {
        private:
            std::map<tileCoordinates, Tile> _tiles;
        public:
            Map();
            ~Map();

            Tile getTile(tileCoordinates) const;
    };
}
