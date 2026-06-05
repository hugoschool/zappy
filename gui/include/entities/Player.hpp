#pragma once

#include "entities/AEntity.hpp"

namespace zappy {
    class Player : public AEntity {
        public:
            Player();
            ~Player();

            void draw() override;
    };
}
