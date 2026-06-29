#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"


namespace zappy {
    class Deraumere : public Material {
        public:
            Deraumere() = delete;
            Deraumere(tileCoordinates, int);
            ~Deraumere();

            std::tuple<int, int, int> getMaterialColor() override;
            std::pair<float, float> getMaterialPosition(std::pair<int, int>) override;
    };
}
