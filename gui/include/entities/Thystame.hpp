#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <Color.hpp>

namespace zappy {
    class Thystame : public Material {
        public:
            Thystame() = delete;
            Thystame(tileCoordinates, int);
            ~Thystame();

            raylib::Color getMaterialColor() override;
            Vector3 getMaterialPosition(std::pair<int, int>) override;
    };
}
