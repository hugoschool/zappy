#include "Raylib.hpp"
#include "IEntity.hpp"
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
        _win.DrawFPS();
        _win.EndDrawing();
    }

    _win.Close();
}

void zappy::RaylibGraphical::drawMap()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    raylib::Rectangle rect(250, 150, mapDimensions.first * 50, mapDimensions.second * 50);
    rect.Draw(raylib::Color::Black());
    drawTiles();
}

void zappy::RaylibGraphical::drawTiles()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            const zappy::Tile tile = _map.getTile(tileCoordinates(x, y));
            raylib::Rectangle rect(250 + (50 * x), 150 + (50 * y), 50, 50);
            rect.DrawLines(raylib::Color::Blue());
        }
    }
}

void zappy::RaylibGraphical::drawText(std::string str, int X, int Y)
{

}
