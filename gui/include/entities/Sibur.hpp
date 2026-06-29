#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"


namespace zappy {
    class Sibur : public Material {
        public:
            Sibur() = delete;
            Sibur(tileCoordinates, int);
            ~Sibur();

            std::tuple<int, int, int> getMaterialColor() override;
            std::pair<float, float> getMaterialPosition(std::pair<int, int>) override;
    };
}
