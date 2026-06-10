#pragma once

#include "IEntity.hpp"
#include "Tile.hpp"
#include <map>
#include <utility>

namespace zappy {
    class Map {
        private:
            std::map<tileCoordinates, Tile> _tiles;
            std::pair<int, int> _dimensions;

        public:
            Map() = delete;
            Map(int, int);
            ~Map();

            Tile& getTile(tileCoordinates);
            const std::pair<int, int> getDimensions() const;

            void setDimensions(int, int);
    };
}
