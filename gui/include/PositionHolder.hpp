#pragma once

#include "IEntity.hpp"

namespace zappy {

    class PositionHolder {
        public:
            PositionHolder() = delete;
            PositionHolder(tileCoordinates current, tileCoordinates reach, int orientation) {
                _posToReach = floatCoordinates(reach.first, reach.second);
                _orientataion = orientation;
                _iterationAddedValue = floatCoordinates((_posToReach.first - current.first) / 8, (_posToReach.second - current.second) / 8);

            };
            ~PositionHolder() {};

            floatCoordinates _posToReach;
            floatCoordinates _iterationAddedValue;
            int _orientataion;
    };
}
