#pragma once

#include "IRaylibEntities.hpp"

namespace zappy {
    class AEntity : public IRaylibEntities {
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
