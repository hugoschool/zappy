#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"


namespace zappy {
    class Mendiane : public Material {
        public:
            Mendiane() = delete;
            Mendiane(tileCoordinates, int);
            ~Mendiane();

            std::tuple<int, int, int> getMaterialColor() override;
            std::pair<float, float> getMaterialPosition(std::pair<int, int>) override;
    };
}
