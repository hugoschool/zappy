#pragma once

#include "GameplatEntitiesHolder.hpp"
#include "Raylib.hpp"
#include "SafeQueue.hpp"
#include <string>

namespace zappy {
    class RaylibBonus : public RaylibGraphical {
        public:
            RaylibBonus() = delete;
            RaylibBonus(Map &map, GameplayEntitiesHolder &GEH);
            ~RaylibBonus();

            bool runCommands(SafeQueue<std::string> &);

    };
}
