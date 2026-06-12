#pragma once

#include "ModelHolder.hpp"
#include <utility>
namespace zappy {

    using tileCoordinates = std::pair<int, int>;

    class IEntity {
        public:
            virtual ~IEntity() = default;

            virtual tileCoordinates getCoords() const = 0;
            virtual void draw(ModelHolder&, std::pair<int, int>) = 0;
            virtual int getAmount() const = 0;
    };
}
