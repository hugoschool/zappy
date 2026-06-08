#include "Raylib.hpp"
#include "Map.hpp"
#include <iostream>

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map): _map(map)
{}

zappy::RaylibGraphical::~RaylibGraphical()
{}

void zappy::RaylibGraphical::initWindow()
{
    _win.Init(1000, 800, "zappy");
    _win.SetTargetFPS(60);
}

void zappy::RaylibGraphical::loop()
{
    initWindow();
    while (!_win.ShouldClose()) {
        _win.BeginDrawing();
        _win.ClearBackground(raylib::Color::White());
        drawMap();
        _win.EndDrawing();
    }

    _win.Close();
}

void zappy::RaylibGraphical::drawMap()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    raylib::Rectangle rect(250, 150, mapDimensions.first * 50, mapDimensions.second * 50);
    rect.Draw(raylib::Color::Black());
}

void zappy::RaylibGraphical::drawTile()
{

}

void zappy::RaylibGraphical::drawText(std::string str, int X, int Y)
{

}
