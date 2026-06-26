#pragma once

#include "IRaylibEntities.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace zappy {
    class Tile {
        private:
            tileCoordinates _coords;
            Vector3 _displayCoordinates;
            std::vector<std::shared_ptr<IRaylibEntities>> _entities;
            bool _selected;
        public:
            Tile() = delete;
            Tile(int X, int Y, std::pair<int, int> mapDimensions);
            ~Tile();

            tileCoordinates getCoords() const;
            Vector3 getDisplayCoordinates() const;
            void setDisplayCoordinates(Vector3 displayCoordinates);
            void addEntity(std::shared_ptr<IRaylibEntities>);
            void removeEntity(std::shared_ptr<IRaylibEntities>);
            std::vector<std::shared_ptr<IRaylibEntities>>& getEntities();
            void clear();
            void setSelectedState(bool selectedState);
            bool isSelected();
        };
}
