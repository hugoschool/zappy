#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>

namespace zappy {
    class Linemate : public Material {
        public:
            Linemate() = delete;
            Linemate(tileCoordinates, int);
            ~Linemate();

            raylib::Color getMaterialColor() override;
            Vector3 getMaterialPosition(std::pair<int, int>) override;
    };
}
