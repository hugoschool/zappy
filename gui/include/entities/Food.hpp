#pragma once

#include "IEntity.hpp"
#include "entities/AEntity.hpp"

namespace zappy {
    class Food : public AEntity {
        public:
            Food();
            Food(tileCoordinates);
            ~Food();

            void draw() override;
    };
}
