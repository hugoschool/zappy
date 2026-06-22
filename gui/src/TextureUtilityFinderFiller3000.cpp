#include "TextureUtilityFinderFiller3000.hpp"
#include "Utils.hpp"
#include <filesystem>
#include <raylib.h>
#include <string>

zappy::TUFF::TUFF()
{}

zappy::TUFF::~TUFF()
{}

void zappy::TUFF::getTextures(std::map<int, raylib::Texture2D>& textureMap, std::string filepath)
{
    std::string realPath = zappy::Utils::pathVerify(filepath);
    for (auto file: std::filesystem::directory_iterator(realPath)) {
        raylib::Texture2D texture(file.path());
        if (static_cast<std::string>(file.path()).find("Base_color") != std::string::npos) {
            textureMap.insert({MATERIAL_MAP_ALBEDO, raylib::Texture2D (file.path())});
        }
        if (static_cast<std::string>(file.path()).find("Height") != std::string::npos) {
            textureMap.insert({MATERIAL_MAP_HEIGHT, raylib::Texture2D (file.path())});
        }
        if (static_cast<std::string>(file.path()).find("Roughness") != std::string::npos) {
            textureMap.insert({MATERIAL_MAP_ROUGHNESS, raylib::Texture2D (file.path())});
        }
        if (static_cast<std::string>(file.path()).find("Normal") != std::string::npos) {
            textureMap.insert({MATERIAL_MAP_NORMAL, raylib::Texture2D (file.path())});
        }
        if (static_cast<std::string>(file.path()).find("Mixed_AO") != std::string::npos) {
            textureMap.insert({MATERIAL_MAP_OCCLUSION, raylib::Texture2D (file.path())});
        }
        if (static_cast<std::string>(file.path()).find("Metallic") != std::string::npos) {
            textureMap.insert({MATERIAL_MAP_METALNESS, raylib::Texture2D (file.path())});
        }
        if (static_cast<std::string>(file.path()).find("Diffuse") != std::string::npos) {
            textureMap.insert({MATERIAL_MAP_DIFFUSE, raylib::Texture2D (file.path())});
        }
    }
}
