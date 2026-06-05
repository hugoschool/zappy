#pragma once

#include "entities/AEntity.hpp"

namespace zappy {
    class Food : public AEntity {
        public:
            Food();
            ~Food();

            void draw() override;
    };
}
