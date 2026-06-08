#pragma once

#include "IEntity.hpp"
#include "raylib-cpp.hpp"

namespace zappy {
    class AEntity : public IEntity {
        protected:
            tileCoordinates _coords;
            raylib::Image _texture;
        public:
            AEntity();
            AEntity(tileCoordinates);
            ~AEntity();

            tileCoordinates getCoords() const override;
            // possiblement abstraire la fonction draw et ajouter un champs protected screenPosition pour definir une position sur la Tile
    };
}
