#pragma once

#include "IEntity.hpp"
#include "ModelHolder.hpp"
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
            Material(MaterialType);
            Material(MaterialType, tileCoordinates, int);
            ~Material();

            raylib::Color getMaterialColor();
            void draw(ModelHolder&) override;
    };
}
