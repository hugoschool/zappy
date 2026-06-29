#pragma once

#include "CircularBuffer.hpp"
#include "GameplatEntitiesHolder.hpp"
#include "Raylib.hpp"
#include <Color.hpp>
#include <Rectangle.hpp>
#include <array>
#include <string>
#include <vector>

namespace zappy {

    enum class screen {
        MENU,
        GAMEPLAY,
        END
    };

    enum class cameraState {
        BEHIND,
        GLOBAL
    };

    class RaylibBonus : public RaylibGraphical {
        public:
            RaylibBonus() = delete;
            RaylibBonus(Map &map, GameplayEntitiesHolder &GEH);
            ~RaylibBonus();

            bool runScreens(CircularBuffer<std::string> &, std::vector<std::string>&);
            bool run() override;

        private:
            screen _screen;

            bool runMenu(CircularBuffer<std::string> &, std::vector<std::string> &);
            bool runGameplay(CircularBuffer<std::string> &);
            void displayItems();
            void updateCamera();

            float _fontSize;

            int _index;

            // Screen Prameters
            float _sizeX;
            float _sizeY;
            float _width;

            // items:
            std::array<std::string, 6> _items;
            std::array<raylib::Color, 6> _colors;
            std::vector<raylib::Rectangle> _itemRec;

            // Camera
            cameraState _cameraState;
        };
}
