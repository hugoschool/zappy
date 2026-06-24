#pragma once

#include "GameplatEntitiesHolder.hpp"
#include "Raylib.hpp"
#include "SafeQueue.hpp"
#include <string>
#include <vector>

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

            bool runScreens(SafeQueue<std::string> &, std::vector<std::string>&);
            bool run() override;

        private:
            screen _screen;

            bool runMenu(SafeQueue<std::string> &, std::vector<std::string> &);
            bool runGameplay(SafeQueue<std::string> &);
            void displayItems();

            float _fontSize;

            int _index;
    };
}
