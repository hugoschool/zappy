#pragma once

#include "IEntity.hpp"
#include "IModelHolder.hpp"
#include "entities/AEntity.hpp"

namespace zappy {

    enum class MaterialType {
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame,
    };

    class Material : public AEntity {
        protected:
            MaterialType _type;
        public:
            Material(MaterialType);
            Material(MaterialType, tileCoordinates, int);
            ~Material();

            virtual raylib::Color getMaterialColor() = 0;
            virtual Vector3 getMaterialPosition(std::pair<int, int>) = 0;
            MaterialType getMaterialType() const;
            void draw(IModelHolder&, std::pair<int, int>) override;
            void drawLowObject(std::pair<int, int>) override;
    };
}
