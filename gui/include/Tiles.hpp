#pragma once

#include "IEntity.hpp"
#include <vector>
namespace zappy {
    class Tile {
        private:
            tileCoordinates _coords;
            std::vector<IEntity> _entities;
        public:
            Tile() = delete;
            Tile(int X, int Y);
            ~Tile();

            tileCoordinates getCoords() const;
            void addEntity(IEntity);
            void removeEntity(IEntity);
            std::vector<IEntity> getEntities() const;
    };
}
