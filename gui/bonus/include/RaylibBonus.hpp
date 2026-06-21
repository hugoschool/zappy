#pragma once

#include "GameplatEntitiesHolder.hpp"
#include "Raylib.hpp"
#include "SafeQueue.hpp"
#include <string>

namespace zappy {

    enum class screen {
        MENU,
        GAMEPLAY,
        END
    };

    class RaylibBonus : public RaylibGraphical {
        public:
            RaylibBonus() = delete;
            RaylibBonus(Map &map, GameplayEntitiesHolder &GEH);
            ~RaylibBonus();

            bool runCommands(SafeQueue<std::string> &);

        private:
            screen _screen;

            bool runMenu(SafeQueue<std::string> &);
            bool runGameplay(SafeQueue<std::string> &);
    };
}
