#pragma once

#include <Shader.hpp>
#include <optional>

namespace zappy {
    constexpr std::string_view PIXELIZER = "assets/shaders/pixelizer.fs";
    constexpr std::string_view SOBEL = "assets/shaders/sobel.fs";
    constexpr std::string_view FISHEYE = "assets/shaders/fisheye.fs";
    constexpr std::string_view POSTERIZATION = "assets/shaders/posterization.fs";
    constexpr std::string_view BLOOM = "assets/shaders/bloom.fs";
    class RaylibShaderHolder {
        public:
            RaylibShaderHolder();
            ~RaylibShaderHolder();

            void initShaders();
            void initShader(std::string, std::optional<std::string>);
            void unloadShaders();
            std::optional<raylib::Shader> &getShader(int&);
        private:
            std::vector<std::optional<raylib::Shader>> _shaderVec;
    };
}
