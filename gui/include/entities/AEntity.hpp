#pragma once

#include "IEntity.hpp"

namespace zappy {
    class AEntity : public IEntity {
        protected:
            tileCoordinates _coords;
        public:
            AEntity();
            ~AEntity();

            tileCoordinates getCoords() const override;
    };
}
