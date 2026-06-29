#pragma once

#include "IEntity.hpp"
#include "entities/AEntity.hpp"

namespace zappy {
    class Food : public AEntity {
        public:
            Food() = delete;
            Food(tileCoordinates, int);
            ~Food();
    };
}
