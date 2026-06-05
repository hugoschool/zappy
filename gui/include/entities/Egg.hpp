#pragma once

#include "entities/AEntity.hpp"

namespace zappy {
    class Egg : public AEntity {
        public:
            Egg();
            ~Egg();

            void draw() override;
    };
}
