#include "ShaderHolder.hpp"
#include <filesystem>
#include "Utils.hpp"

zappy::ShaderHolder::ShaderHolder(): _shaderVec()
{
    _shaderVec.push_back(std::nullopt);
}

zappy::ShaderHolder::~ShaderHolder()
{}

void zappy::ShaderHolder::initShaders()
{
    initShader("assets/shaders/pixelizer.fs", std::nullopt);
    initShader("assets/shaders/sobel.fs", std::nullopt);
}

void zappy::ShaderHolder::initShader(std::string filepath, std::optional<std::string> optfilepath)
{
    std::string realPath = zappy::Utils::pathVerify(filepath);
    if (optfilepath.has_value()) {
        std::string optRealPath = zappy::Utils::pathVerify(optfilepath.value());
        _shaderVec.push_back(LoadShader(optRealPath.c_str(), realPath.c_str()));
        return;
    }
    _shaderVec.push_back(LoadShader(0, realPath.c_str()));
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
