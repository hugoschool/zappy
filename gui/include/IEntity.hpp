#pragma once

#include <utility>
namespace zappy {

    using tileCoordinates = std::pair<int, int>;

    class IEntity {
        public:
            ~IEntity() = default;

            virtual tileCoordinates getCoords() const = 0;
            virtual void draw() = 0;
    };
}
