#pragma once

#include "RaylibModelHolder.hpp"
#include <utility>
namespace zappy {

    using tileCoordinates = std::pair<int, int>;
    using floatCoordinates = std::pair<float, float>;

    class IRaylibEntities {
        public:
            virtual ~IRaylibEntities() = default;

            virtual tileCoordinates getCoords() const = 0;
            virtual void draw(RaylibModelHolder&, std::pair<int, int>) = 0;
            virtual void drawLowObject(std::pair<int, int>) = 0;
            virtual int getAmount() const = 0;
    };
}
