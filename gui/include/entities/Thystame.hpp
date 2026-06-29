#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"


namespace zappy {
    class Thystame : public Material {
        public:
            Thystame() = delete;
            Thystame(tileCoordinates, int);
            ~Thystame();

            std::tuple<int, int, int> getMaterialColor() override;
            std::pair<float, float> getMaterialPosition(std::pair<int, int>) override;
    };
}
