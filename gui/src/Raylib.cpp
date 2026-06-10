#include "Raylib.hpp"
#include "IEntity.hpp"
#include "Map.hpp"
#include <Camera3D.hpp>
#include <Color.hpp>
#include <Keyboard.hpp>
#include <Material.hpp>
#include <Mouse.hpp>
#include <Vector3.hpp>
#include <memory>
#include <raylib.h>
#include <vector>

zappy::RaylibGraphical::RaylibGraphical(zappy::Map &map): _map(map), _window(),
    _camera(), _modelHolder(), _moveCamera(false)
{
    initWindow();
    initCamera();
    _modelHolder.initModels();

}

zappy::RaylibGraphical::~RaylibGraphical()
{
    _modelHolder.unloadModels();
    _window.Close();
}

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

bool zappy::RaylibGraphical::run()
{
    bool exit = true;
    //-------------//
    //-Move-Camera-//
    //-------------//
    if (raylib::Mouse::IsButtonDown(MOUSE_BUTTON_LEFT)) {
        _moveCamera = true;
        _camera.Update(CAMERA_THIRD_PERSON);
    }
    if (_moveCamera && raylib::Mouse::IsButtonUp(MOUSE_BUTTON_LEFT)) {
        _moveCamera = false;
        _camera.Update(CAMERA_CUSTOM);
    }
    if (_moveCamera == false) {
        float scroll = raylib::Mouse::GetWheelMove();
        if (scroll != 0) {
            _camera.Update(CAMERA_THIRD_PERSON);
        } else {
            _camera.Update(CAMERA_CUSTOM);
        }
    }
    if (_window.ShouldClose())
        exit = false;

    //------//
    //-Draw-//
    //------//
    _window.BeginDrawing();
    _window.ClearBackground(raylib::Color::RayWhite());

    BeginMode3D(_camera);

    drawTiles();

    _window.DrawFPS();
    EndMode3D();

    _window.EndDrawing();
    return exit;
}

void zappy::RaylibGraphical::drawTiles()
{
    const std::pair<int, int> mapDimensions = _map.getDimensions();

    for (int y = 0; y < mapDimensions.second; y++) {
        for (int x = 0; x < mapDimensions.first; x++) {
            zappy::Tile& tile = _map.getTile(tileCoordinates(x, y));
            Vector3 position = { static_cast<float>(x) - mapDimensions.first / 2.0f, 0.0f, static_cast<float>(y) - mapDimensions.second / 2.0f};
            DrawCube(position, 1.0f, 0.1f, 1.0f, raylib::Color::Green());
            DrawCubeWires(position, 1.0f, 0.1f, 1.0f, raylib::Color::Black());
            std::vector<std::shared_ptr<IEntity>> &entities = tile.getEntities();
            for (auto &entity: entities) {
                entity->draw(_modelHolder);
            }
        }
    }
}

void zappy::RaylibGraphical::drawText(std::string str, int X, int Y)
{
    static_cast<void>(str);
    static_cast<void>(X);
    static_cast<void>(Y);
}
