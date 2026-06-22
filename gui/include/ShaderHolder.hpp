#pragma once

#include <Shader.hpp>
#include <optional>

namespace zappy {
    class ShaderHolder {
        public:
            ShaderHolder();
            ~ShaderHolder();

            void initShaders();
            void initShader(std::string, std::optional<std::string>);
            void unloadShaders();
            std::optional<raylib::Shader> &getShader(int&);
        private:
            std::vector<std::optional<raylib::Shader>> _shaderVec;
    };
}
