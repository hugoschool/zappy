#include "RaylibModelHolder.hpp"
#include <filesystem>
#include <raylib.h>
#include "TextureUtilityFinderFiller3000.hpp"

zappy::RaylibModelHolder::RaylibModelHolder(): _materialModel(), _foodModel(), _eggModel(), _playerModel(), _materialTextureMap(), _foodTextureMap(), _eggTextureMap(), _playerAnimations()
{}

zappy::RaylibModelHolder::~RaylibModelHolder()
{}

void zappy::RaylibModelHolder::initModel(raylib::Model& model, std::string filepath)
{
    if (!std::filesystem::exists(filepath)) {
        filepath = "gui/" + filepath;
    } else {}
    model.Load(filepath);
}

void zappy::RaylibModelHolder::initPlayerModelAndAnimations(std::string filepath)
{
    if (!std::filesystem::exists(filepath)) {
        filepath = "gui/" + filepath;
    } else {}
    _playerModel = LoadModel(filepath.c_str());
    _playerAnimations = LoadModelAnimations(filepath.c_str(), &playerAnimationsCount);
    _playerModel.UpdateAnimation(_playerAnimations[3], _playerAnimations[3].keyframeCount);
}

void zappy::RaylibModelHolder::initModels()
{
    initModel(_materialModel, "assets/OBJ/stylized_crystal_SM.obj");
    initModel(_foodModel, "assets/OBJ/turkey_leg.obj");
    initModel(_eggModel, "assets/OBJ/Egg_Low.obj");
    initPlayerModelAndAnimations("assets/robot.glb");
    zappy::TUFF::getMaterialsTextures(_materialTextureMap, "assets/Textures/PNG");
    zappy::TUFF::getMaterialsTextures(_eggTextureMap, "assets/Textures/Egg_Textures2K");
    zappy::TUFF::getMaterialsTextures(_foodTextureMap, "assets/Textures/food_texture");
    for (auto &materialTexture: _materialTextureMap) {
        _materialModel.materials[0].maps[materialTexture.first].texture = materialTexture.second;
    }
    for (auto &foodTexture: _foodTextureMap) {
        _foodModel.materials[0].maps[foodTexture.first].texture = foodTexture.second;
    }
    for (auto &eggTexture: _eggTextureMap) {
        _eggModel.materials[0].maps[eggTexture.first].texture = eggTexture.second;
    }
}

void zappy::RaylibModelHolder::unloadModels()
{
    for (auto &materialTexture: _materialTextureMap) {
        materialTexture.second.Unload();
    }
    for (auto &foodTexture: _foodTextureMap) {
        foodTexture.second.Unload();
    }
    for (auto &eggTexture: _eggTextureMap) {
        eggTexture.second.Unload();
    }
    _materialModel.Unload();
    _foodModel.Unload();
    _eggModel.Unload();
    UnloadModelAnimations(_playerAnimations, playerAnimationsCount);
    _playerModel.Unload();
}

raylib::Model& zappy::RaylibModelHolder::getMaterialModel()
{
    return _materialModel;
}

raylib::Model& zappy::RaylibModelHolder::getFoodModel()
{
    return _foodModel;
}

raylib::Model& zappy::RaylibModelHolder::getEggModel()
{
    return _eggModel;
}

raylib::Model& zappy::RaylibModelHolder::getPlayerModel()
{
    return _playerModel;
}

ModelAnimation *zappy::RaylibModelHolder::getPlayerAnimations()
{
    return _playerAnimations;
}
