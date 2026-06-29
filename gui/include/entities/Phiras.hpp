#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"


namespace zappy {
    class Phiras : public Material {
        public:
            Phiras() = delete;
            Phiras(tileCoordinates, int);
            ~Phiras();

            std::tuple<int, int, int> getMaterialColor() override;
            std::pair<float, float> getMaterialPosition(std::pair<int, int>) override;
    };
}
