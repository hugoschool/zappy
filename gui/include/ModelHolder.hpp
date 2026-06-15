#pragma once

#include <Model.hpp>
#include <ModelAnimation.hpp>
#include <Texture.hpp>
#include <map>
#include <memory>

namespace zappy {
    class ModelHolder {
        private:
            raylib::Model _materialModel;
            raylib::Model _foodModel;
            raylib::Model _eggModel;
            raylib::Model _playerModel;
            std::map<int, raylib::Texture2D> _materialTextureMap;
            std::map<int, raylib::Texture2D> _foodTextureMap;
            std::map<int, raylib::Texture2D> _eggTextureMap;
            std::vector<raylib::ModelAnimation>_playerAnimations;
        public:
            ModelHolder();
            ~ModelHolder();

            void initModel(raylib::Model&, std::string);
            void initModelAnimations(std::vector<raylib::ModelAnimation>&, std::string);
            void initModels();
            void unloadModels();
            raylib::Model& getMaterialModel();
            raylib::Model& getFoodModel();
            raylib::Model& getEggModel();
            raylib::Model& getPlayerModel();
    };
}
