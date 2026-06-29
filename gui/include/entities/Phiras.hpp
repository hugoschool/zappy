#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>

namespace zappy {
    class Phiras : public Material {
        public:
            Phiras() = delete;
            Phiras(tileCoordinates, int);
            ~Phiras();

            raylib::Color getMaterialColor() override;
            Vector3 getMaterialPosition(std::pair<int, int>) override;
    };
}
