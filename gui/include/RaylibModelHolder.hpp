#pragma once

#include "IModelHolder.hpp"
#include <Model.hpp>
#include <ModelAnimation.hpp>
#include <Texture.hpp>
#include <map>
#include <memory>

namespace zappy {
    constexpr int ROBOT_INCANTATION = 0;
    constexpr int ROBOT_IDLE = 2;
    constexpr int ROBOT_RUN = 6;
    class RaylibModelHolder : IModelHolder {
        private:
            raylib::Model _materialModel;
            raylib::Model _foodModel;
            raylib::Model _eggModel;
            raylib::Model _playerModel;
            std::map<int, raylib::Texture2D> _materialTextureMap;
            std::map<int, raylib::Texture2D> _foodTextureMap;
            std::map<int, raylib::Texture2D> _eggTextureMap;
            ModelAnimation* _playerAnimations;

            raylib::Texture2D _bkg;
            float _bkgScroll;
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
            ModelAnimation* getPlayerAnimations();
            raylib::Texture2D& getBackground();
            int updateBackgroundScroll();
    };
}
