#include "ModelHolder.hpp"
#include <filesystem>
#include "TextureUtilityFinderFiller3000.hpp"

zappy::ModelHolder::ModelHolder(): _materialModel(), _foodModel(), _eggModel(), _materialTextureMap(), _foodTextureMap(), _eggTextureMap()
{}

zappy::ModelHolder::~ModelHolder()
{}

void zappy::ModelHolder::initModel(raylib::Model& model, std::string filepath)
{
    if (!std::filesystem::exists(filepath)) {
        filepath = "gui/" + filepath;
    } else {}
    model.Load(filepath);
}

void zappy::ModelHolder::initModels()
{
    initModel(_materialModel, "assets/OBJ/stylized_crystal_SM.obj");
    initModel(_foodModel, "assets/OBJ/turkey_leg.obj");
    initModel(_eggModel, "assets/OBJ/egg_obj.obj");
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

void zappy::ModelHolder::unloadModels()
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
}

raylib::Model& zappy::ModelHolder::getMaterialModel()
{
    return _materialModel;
}

raylib::Model& zappy::ModelHolder::getFoodModel()
{
    return _foodModel;
}

raylib::Model& zappy::ModelHolder::getEggModel()
{
    return _eggModel;
}
