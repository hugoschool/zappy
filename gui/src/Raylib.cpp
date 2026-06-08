#include "Raylib.hpp"
#include "IEntity.hpp"
#include "Map.hpp"
#include <Camera3D.hpp>
#include <Color.hpp>
#include <Keyboard.hpp>
#include <Material.hpp>
#include <Mouse.hpp>
#include <Vector3.hpp>
#include <filesystem>
#include <iostream>
#include <raylib.h>

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map): _map(map), _window(), _camera(), _materialModel(), _materialTextures()
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

void zappy::RaylibGraphical::initModels()
{
    _materialModel.Load("OBJ/stylized_crystal_SM.obj");
    int i = 0;
    for (auto file: std::filesystem::directory_iterator("Textures/PNG")) {
        std::cout << file.path() << std::endl;
        raylib::Texture2D texture(file.path());
        _materialTextures.push_back(std::move(texture));
        _materialModel.materials[0].maps[textNums[i]].texture = _materialTextures.back();
        i++;
    }
}

void zappy::RaylibGraphical::loop()
{
    bool moveCamera = false;
    initWindow();
    initCamera();
    initModels();
    while (!_window.ShouldClose()) {
        //-------------//
        //-Move-Camera-//
        //-------------//
        if (raylib::Mouse::IsButtonDown(MOUSE_BUTTON_LEFT)) {
            moveCamera = true;
            _camera.Update(CAMERA_THIRD_PERSON);
        }
        if (moveCamera && raylib::Mouse::IsButtonUp(MOUSE_BUTTON_LEFT)) {
            moveCamera = false;
            _camera.Update(CAMERA_CUSTOM);
        }
        if (moveCamera == false) {
            float scroll = raylib::Mouse::GetWheelMove();
            if (scroll != 0) {
                _camera.Update(CAMERA_THIRD_PERSON);
            } else {
                _camera.Update(CAMERA_CUSTOM);
            }
        }

        //------//
        //-Draw-//
        //------//
        _window.BeginDrawing();
        _window.ClearBackground(raylib::Color::RayWhite());

        BeginMode3D(_camera);

        drawTiles();
        _materialModel.Draw(Vector3(0, 1, 0), 1.0f, raylib::Color::Blue());

        EndMode3D();

        _window.EndDrawing();
    }
    unloadModels();
    _window.Close();
}

void zappy::RaylibGraphical::unloadModels()
{
    for (raylib::Texture2D &text: _materialTextures) {
        text.Unload();
    }
    _materialModel.Unload();
}

void zappy::RaylibGraphical::drawTiles()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            const zappy::Tile tile = _map.getTile(tileCoordinates(x, y));
            Vector3 position = { static_cast<float>(x) - mapDimensions.first / 2.0f, 0.0f, static_cast<float>(y) - mapDimensions.second / 2.0f};
            DrawCube(position, 1.0f, 0.1f, 1.0f, raylib::Color::Green());
            DrawCubeWires(position, 1.0f, 0.1f, 1.0f, raylib::Color::Black());
        }
    }
}

void zappy::RaylibGraphical::drawText(std::string str, int X, int Y)
{

}
