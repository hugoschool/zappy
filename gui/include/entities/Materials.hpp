#pragma once

#include "IEntity.hpp"
#include "entities/AEntity.hpp"
#include <tuple>

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

            virtual std::tuple<int, int, int> getMaterialColor() = 0;
            virtual std::pair<float, float> getMaterialPosition(std::pair<int, int>) = 0;
            MaterialType getMaterialType() const;
    };
}
