#pragma once

#include "ModelHolder.hpp"
#include <utility>
namespace zappy {

    using tileCoordinates = std::pair<int, int>;

    class IEntity {
        public:
            virtual ~IEntity() = default;

            virtual tileCoordinates getCoords() const = 0;
            virtual void draw(ModelHolder&) = 0;
    };
}
