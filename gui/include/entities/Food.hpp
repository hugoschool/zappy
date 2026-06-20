#pragma once

#include "IEntity.hpp"
#include "RaylibModelHolder.hpp"
#include "entities/AEntity.hpp"

namespace zappy {
    class Food : public AEntity {
        public:
            Food() = delete;
            Food(tileCoordinates, int);
            ~Food();

            void draw(RaylibModelHolder&, std::pair<int, int>) override;
    };
}
