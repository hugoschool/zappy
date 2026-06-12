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
            Vector3 getMaterialPosition(std::pair<int, int>);
            MaterialType getMaterialType() const;
            void draw(ModelHolder&, std::pair<int, int>) override;
    };
}
