#pragma once

#include "IEntity.hpp"
#include "ModelHolder.hpp"
#include "entities/AEntity.hpp"

namespace zappy {
    class Egg : public AEntity {
        public:
            Egg() = delete;
            Egg(tileCoordinates, int);
            ~Egg();

            void draw(ModelHolder&) override;
    };
}
