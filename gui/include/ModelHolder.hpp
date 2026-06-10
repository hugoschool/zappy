#pragma once

#include <Model.hpp>
#include <Texture.hpp>
#include <map>

namespace zappy {
    class ModelHolder {
        private:
            raylib::Model _materialModel;
            raylib::Model _foodModel;
            raylib::Model _eggModel;
            std::map<int, raylib::Texture2D> _materialTextureMap;
            std::map<int, raylib::Texture2D> _foodTextureMap;
            std::map<int, raylib::Texture2D> _eggTextureMap;
        public:
            ModelHolder();
            ~ModelHolder();

            void initModel(raylib::Model&, std::string);
            void initModels();
            void unloadModels();
            raylib::Model& getMaterialModel();
            raylib::Model& getFoodModel();
            raylib::Model& getEggModel();
    };
}
