#pragma once

#include "IEntity.hpp"
#include <memory>
#include <vector>
namespace zappy {
    class Tile {
        private:
            tileCoordinates _coords;
            std::vector<std::shared_ptr<IEntity>> _entities;
        public:
            Tile();
            Tile(int X, int Y);
            ~Tile();

            tileCoordinates getCoords() const;
            void addEntity(std::shared_ptr<IEntity>);
            void removeEntity(std::shared_ptr<IEntity>);
            std::vector<std::shared_ptr<IEntity>>& getEntities();
            void clear();
        };
}
