#pragma once

#include "IEntity.hpp"

namespace zappy {
    class AEntity : public IEntity {
        protected:
            tileCoordinates _coords;
            int _amount;
        public:
            AEntity() = delete;
            AEntity(tileCoordinates, int amount);
            ~AEntity();

            tileCoordinates getCoords() const override;
            int getAmount() const override;
            // possiblement abstraire la fonction draw et ajouter un champs protected screenPosition pour definir une position sur la Tile
    };
}
