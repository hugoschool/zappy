#pragma once

namespace zappy {
    class IParticles {
        public:
            ~IParticles() = default;

            virtual void update() = 0;
            virtual void emit() = 0;
            virtual int getTail() = 0;
            virtual int getHead() = 0;
    };
}
