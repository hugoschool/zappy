#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"


namespace zappy {
    class Linemate : public Material {
        public:
            Linemate() = delete;
            Linemate(tileCoordinates, int);
            ~Linemate();

            std::tuple<int, int, int> getMaterialColor() override;
            std::pair<float, float> getMaterialPosition(std::pair<int, int>) override;
    };
}
