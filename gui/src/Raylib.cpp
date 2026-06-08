#include "Raylib.hpp"
#include "IEntity.hpp"
#include "Map.hpp"
#include <Camera3D.hpp>
#include <Color.hpp>
#include <Vector3.hpp>
#include <iostream>
#include <raylib.h>

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map): _map(map), _window(), _camera()
{}

zappy::RaylibGraphical::~RaylibGraphical()
{}

void zappy::RaylibGraphical::initWindow()
{
    _window.Init(1000, 800, "zappy");
    _window.SetTargetFPS(60);
}

void zappy::RaylibGraphical::initCamera()
{
    _camera.SetPosition({0.0, 10.0, 10.0}); // Camera position
    _camera.SetTarget({0, 0, 0}); // Camera looking at point
    _camera.SetUp({ 0.0f, 1.0f, 0.0f }); // Camera up vector (rotation towards target)
    _camera.SetFovy(45); // Camera field-of-view Y
    _camera.SetProjection(CAMERA_PERSPECTIVE);
}

void zappy::RaylibGraphical::loop()
{
    raylib::Vector3 cubePosition = {0, 0, 0};

    initWindow();
    initCamera();
    while (!_window.ShouldClose()) {
        _window.BeginDrawing();
        _window.ClearBackground(raylib::Color::White());
        BeginMode3D(_camera);

        // drawMap();
        DrawCube(cubePosition, 2, 2, 2, raylib::Color::Red());
        DrawCubeWires(cubePosition, 2, 2, 2, raylib::Color::Maroon());
        DrawGrid(10, 1);

        EndMode3D();
        _window.EndDrawing();
    }

    _window.Close();
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
