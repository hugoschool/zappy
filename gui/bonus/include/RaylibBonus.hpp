#pragma once

#include "GameplatEntitiesHolder.hpp"
#include "Raylib.hpp"
namespace zappy {
    class RaylibBonus : public RaylibGraphical {
        public:
            RaylibBonus() = delete;
            RaylibBonus(Map &map, GameplayEntitiesHolder &GEH);
            ~RaylibBonus();
    };
}
