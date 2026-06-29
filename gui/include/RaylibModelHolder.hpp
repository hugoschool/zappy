#pragma once

#include "IModelHolder.hpp"
#include <Model.hpp>
#include <ModelAnimation.hpp>
#include <Texture.hpp>
#include <map>
#include <raylib.h>

namespace zappy {
    constexpr int ROBOT_INCANTATION = 0;
    constexpr int ROBOT_IDLE = 2;
    constexpr int ROBOT_RUN = 6;
    constexpr int ROBOT_DEATH = 1;
    constexpr int ROBOT_TAKE = 9;
    constexpr int ROBOT_DROP = 7;
    constexpr int ROBOT_HIT = 5;

    constexpr std::string_view MATERIAL_MODEL = "assets/OBJ/stylized_crystal_SM.obj";
    constexpr std::string_view FOOD_MODEL = "assets/OBJ/turkey_leg.obj";
    constexpr std::string_view EGG_MODEL = "assets/OBJ/egg.obj";
    constexpr std::string_view ROBOT = "assets/robot.glb";
    constexpr std::string_view MATERIAL_TEXTURES = "assets/Textures/PNG";
    constexpr std::string_view EGG_TEXTURES = "assets/Textures/Egg_Textures2K";
    constexpr std::string_view FOOD_TEXTURES = "assets/Textures/food_texture";
    constexpr std::string_view BACKGROUND = "assets/bkg.png";
    constexpr std::string_view CONFETTI = "assets/confetti.png";
    constexpr std::string_view GRASS = "assets/grass.png";
    constexpr std::string_view MUSIC = "assets/win.mp3";
    class RaylibModelHolder : public IModelHolder {
        private:
            raylib::Model _materialModel;
            raylib::Model _foodModel;
            raylib::Model _eggModel;
            raylib::Model _playerModel;
            std::map<int, raylib::Texture2D> _materialTextureMap;
            std::map<int, raylib::Texture2D> _foodTextureMap;
            std::map<int, raylib::Texture2D> _eggTextureMap;
            ModelAnimation* _playerAnimations;
            raylib::Model _grassModel;

            raylib::Texture2D _bkg;
            raylib::Texture2D _grassTexture;
            float _bkgScroll;

            raylib::Texture2D _endBg;

            Music _music;
            bool _playing;

        public:
            RaylibModelHolder();
            ~RaylibModelHolder();
            int playerAnimationsCount;

            void initModel(raylib::Model&, std::string);
            void initPlayerModelAndAnimations(std::string);
            void initModels() override;
            void unloadModels() override;
            raylib::Model& getMaterialModel();
            raylib::Model& getFoodModel();
            raylib::Model& getEggModel();
            raylib::Model& getPlayerModel();
            raylib::Model& getGrassModel();
            ModelAnimation* getPlayerAnimations();
            raylib::Texture2D& getBackground();
            int updateBackgroundScroll();
            raylib::Texture2D &getEndScreen();
            int updateEndBackgroundScroll();
            void updateMusic();
    };
}
