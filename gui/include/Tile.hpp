#pragma once

#include "IEntity.hpp"
#include "Utils.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace zappy {
    class Tile {
        private:
            tileCoordinates _coords;
            Vector3D _displayCoordinates;
            std::vector<std::shared_ptr<IEntity>> _entities;
            bool _selected;
        public:
            Tile() = delete;
            Tile(int X, int Y, std::pair<int, int> mapDimensions);
            ~Tile();

            tileCoordinates getCoords() const;
            Vector3D getDisplayCoordinates() const;
            void setDisplayCoordinates(Vector3D displayCoordinates);
            void addEntity(std::shared_ptr<IEntity>);
            void removeEntity(std::shared_ptr<IEntity>);
            std::vector<std::shared_ptr<IEntity>>& getEntities();
            void clear();
            void setSelectedState(bool selectedState);
            bool isSelected();
        };
}
