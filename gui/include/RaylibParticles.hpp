#pragma once

#include "IEntity.hpp"
#include "IParticles.hpp"
#include <Color.hpp>
#include <array>
#include <optional>
#include <vector>
namespace zappy {

    #define MAX_PARTICLES 30

    class ParticlesData {
        public:
            Vector3 _position;
            Vector3 _velocity;
            float _radius;
            raylib::Color _color;
            float _lifetime;
            bool _alive;

            ParticlesData() = delete;
            ParticlesData(Vector3);
            ~ParticlesData();

            void reset(Vector3);
    };

    class RaylibParticles : public IParticles {
        private:
            int _emissionRate;
            std::array<std::optional<ParticlesData>, MAX_PARTICLES> _dataArray;
            tileCoordinates _coords;
            Vector3 _displayCoords;
            int _head;
            int _tail;
        public:
            RaylibParticles();
            RaylibParticles(tileCoordinates, std::pair<int, int>);
            ~RaylibParticles();

            void update() override;
            void emit() override;
            int getTail() override;
            int getHead() override;
            std::array<std::optional<ParticlesData>, MAX_PARTICLES> getDataArray();
    };
}
