#pragma once

#include "IEntity.hpp"
#include "entities/AEntity.hpp"

namespace zappy {

    enum MaterialType {
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame,
    };

    class Material : public AEntity {
        private:
            MaterialType _type;
        public:
            Material();
            Material(tileCoordinates);
            ~Material();

            void draw() override;
    };
}
