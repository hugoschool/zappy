#pragma once

#include "IEntity.hpp"
#include "entities/AEntity.hpp"

namespace zappy {
    class Egg : public AEntity {
        public:
            Egg();
            Egg(tileCoordinates);
            ~Egg();

            void draw() override;
    };
}
