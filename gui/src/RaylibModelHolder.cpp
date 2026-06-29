#include "RaylibModelHolder.hpp"
#include <Image.hpp>
#include <raylib.h>
#include "TextureUtilityFinderFiller3000.hpp"
#include "Utils.hpp"

zappy::RaylibModelHolder::RaylibModelHolder(): _materialModel(), _foodModel(),
    _eggModel(), _playerModel(), _materialTextureMap(), _foodTextureMap(),
    _eggTextureMap(), _playerAnimations(), _grassModel(), _bkg(),
    _grassTexture(), _bkgScroll(0), _endBg(), _music(), _playing(false)
{}

zappy::RaylibModelHolder::~RaylibModelHolder()
{}

void zappy::RaylibModelHolder::initModel(raylib::Model& model, std::string filepath)
{
    std::string realPath = zappy::Utils::pathVerify(filepath);
    model.Load(realPath);
}

void zappy::RaylibModelHolder::initPlayerModelAndAnimations(std::string filepath)
{
    std::string realPath = zappy::Utils::pathVerify(filepath);
    _playerModel = LoadModel(realPath.c_str());
    _playerAnimations = LoadModelAnimations(realPath.c_str(), &playerAnimationsCount);
    _playerModel.UpdateAnimation(_playerAnimations[3], _playerAnimations[3].keyframeCount);
}

void zappy::RaylibModelHolder::initModels()
{
    initModel(_materialModel, "assets/OBJ/stylized_crystal_SM.obj");
    initModel(_foodModel, "assets/OBJ/turkey_leg.obj");
    initModel(_eggModel, "assets/OBJ/egg.obj");
    initPlayerModelAndAnimations("assets/robot.glb");
    zappy::TUFF::getTextures(_materialTextureMap, "assets/Textures/PNG");
    zappy::TUFF::getTextures(_eggTextureMap, "assets/Textures/Egg_Textures2K");
    zappy::TUFF::getTextures(_foodTextureMap, "assets/Textures/food_texture");
    for (auto &materialTexture: _materialTextureMap) {
        _materialModel.materials[0].maps[materialTexture.first].texture = materialTexture.second;
    }
    for (auto &foodTexture: _foodTextureMap) {
        _foodModel.materials[0].maps[foodTexture.first].texture = foodTexture.second;
    }
    for (auto &eggTexture: _eggTextureMap) {
        _eggModel.materials[0].maps[eggTexture.first].texture = eggTexture.second;
    }
    _bkg.Load(zappy::Utils::pathVerify("assets/bkg.png"));
    _endBg.Load(zappy::Utils::pathVerify("assets/confetti.png"));
    _grassTexture.Load(zappy::Utils::pathVerify("assets/grass.png"));
    _grassModel = LoadModelFromMesh(GenMeshCube(1, 0.1f, 1));
    _grassModel.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = _grassTexture;
    _music = LoadMusicStream(zappy::Utils::pathVerify("assets/win.mp3").c_str());
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
    _bkg.Unload();
    _grassTexture.Unload();
    _grassModel.Unload();
    _endBg.Unload();
}

int zappy::RaylibModelHolder::updateBackgroundScroll()
{
    _bkgScroll += 0.75f;
    if (_bkgScroll >= _bkg.width * 2)
        _bkgScroll = 0;
    return _bkgScroll;
}

int zappy::RaylibModelHolder::updateEndBackgroundScroll()
{
    _bkgScroll += 0.75f;
    if (_bkgScroll >= _endBg.height * 0.5)
        _bkgScroll = 0;
    return _bkgScroll;
}

raylib::Texture2D& zappy::RaylibModelHolder::getBackground()
{
    return _bkg;
}

raylib::Texture2D& zappy::RaylibModelHolder::getEndScreen()
{
    return _endBg;
}

raylib::Model& zappy::RaylibModelHolder::getGrassModel()
{
    return _grassModel;
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

void zappy::RaylibModelHolder::updateMusic()
{
    if (!_playing) {
        PlayMusicStream(_music);
        _playing = true;
    }
    UpdateMusicStream(_music);
}
