#include "ShaderHolder.hpp"
#include <filesystem>
#include <string>

zappy::ShaderHolder::ShaderHolder(): _shaderVec()
{
    _shaderVec.push_back(std::nullopt);
}

zappy::ShaderHolder::~ShaderHolder()
{}

void zappy::ShaderHolder::initShaders()
{
    initShader("assets/shaders/pixelizer.fs");
    initShader("assets/shaders/sobel.fs");
}

void zappy::ShaderHolder::initShader(std::string filepath)
{
    std::string tempfilepath(filepath);

    if (!std::filesystem::exists(filepath)) {
        filepath = "gui/" + filepath;
        if (!std::filesystem::exists(filepath)) {
            filepath = "../" + tempfilepath;
        }
    } else {}
    _shaderVec.push_back(LoadShader(0, filepath.c_str()));
}

void zappy::ShaderHolder::unloadShaders()
{
    for (auto &shader: _shaderVec) {
        if (shader.has_value())
            shader.value().Unload();
    }
}

std::optional<raylib::Shader> &zappy::ShaderHolder::getShader(int &index)
{
    if (static_cast<std::size_t>(index) >= _shaderVec.size()) {
        index = 0;
    }
    if (index < 0) {
        index = _shaderVec.size();
    }
    return _shaderVec.at(index);
}
