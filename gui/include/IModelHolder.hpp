#pragma once

#include <Model.hpp>
#include <ModelAnimation.hpp>
#include <Texture.hpp>

namespace zappy {
    class IModelHolder {
        public:
            ~IModelHolder() = default;

            virtual void initModels() = 0;
            virtual void unloadModels() = 0;
    };
}
