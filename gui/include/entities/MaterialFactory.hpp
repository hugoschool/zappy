#pragma once

#include "IEntity.hpp"
#include "entities/Materials.hpp"
#include <functional>
#include <map>
#include <memory>

namespace zappy {
    class MaterialFactory {
        public:
            MaterialFactory();
            ~MaterialFactory();

            std::shared_ptr<IEntity> getMaterial(MaterialType, tileCoordinates, int);

        private:
            std::map<MaterialType, std::function<std::shared_ptr<IEntity>(tileCoordinates, int)>> _materials;
    };
}
