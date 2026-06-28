#pragma once

#include "IEntity.hpp"
#include "IModelHolder.hpp"
#include "entities/AEntity.hpp"

namespace zappy {
    class Food : public AEntity {
        public:
            Food() = delete;
            Food(tileCoordinates, int);
            ~Food();

            void draw(IModelHolder&, std::pair<int, int>) override;
            void drawLowObject(std::pair<int, int>) override;
    };
}
