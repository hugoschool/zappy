#include "RaylibShaderHolder.hpp"
#include "Utils.hpp"
#include <string>

zappy::RaylibShaderHolder::RaylibShaderHolder(): _shaderVec()
{
    _shaderVec.push_back(std::nullopt);
}

zappy::RaylibShaderHolder::~RaylibShaderHolder()
{}

void zappy::RaylibShaderHolder::initShaders()
{
    initShader(std::string(PIXELIZER), std::nullopt);
    initShader(std::string(SOBEL), std::nullopt);
    initShader(std::string(FISHEYE), std::nullopt);
    initShader(std::string(POSTERIZATION), std::nullopt);
    initShader(std::string(BLOOM), std::nullopt);
}

void zappy::RaylibShaderHolder::initShader(std::string filepath, std::optional<std::string> optfilepath)
{
    std::string realPath = zappy::Utils::pathVerify(filepath);
    if (optfilepath.has_value()) {
        std::string optRealPath = zappy::Utils::pathVerify(optfilepath.value());
        _shaderVec.push_back(LoadShader(optRealPath.c_str(), realPath.c_str()));
        return;
    }
    _shaderVec.push_back(LoadShader(0, realPath.c_str()));
}

void zappy::RaylibShaderHolder::unloadShaders()
{
    for (auto &shader: _shaderVec) {
        if (shader.has_value())
            shader.value().Unload();
    }
}

std::optional<raylib::Shader> &zappy::RaylibShaderHolder::getShader(int &index)
{
    if (static_cast<std::size_t>(index) >= _shaderVec.size()) {
        index = 0;
    }
    if (index < 0) {
        index = _shaderVec.size();
    }
    return _shaderVec.at(index);
}
