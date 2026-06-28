#pragma once

#include "IModelHolder.hpp"
#include <utility>
namespace zappy {

    using tileCoordinates = std::pair<int, int>;
    using floatCoordinates = std::pair<float, float>;

    class IEntity {
        public:
            virtual ~IEntity() = default;

            virtual tileCoordinates getCoords() const = 0;
            virtual void draw(IModelHolder&, std::pair<int, int>) = 0;
            virtual void drawLowObject(std::pair<int, int>) = 0;
            virtual int getAmount() const = 0;
    };
}
