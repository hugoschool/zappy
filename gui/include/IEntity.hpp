#pragma once

#include <utility>
namespace zappy {

    using tileCoordinates = std::pair<int, int>;
    using floatCoordinates = std::pair<float, float>;

    class IEntity {
        public:
            virtual ~IEntity() = default;

            virtual tileCoordinates getCoords() const = 0;
            virtual int getAmount() const = 0;
    };
}
