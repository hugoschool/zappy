#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>

namespace zappy {
    class Deraumere : public Material {
        public:
            Deraumere() = delete;
            Deraumere(tileCoordinates, int);
            ~Deraumere();

            raylib::Color getMaterialColor() override;
            Vector3 getMaterialPosition(std::pair<int, int>) override;
    };
}
