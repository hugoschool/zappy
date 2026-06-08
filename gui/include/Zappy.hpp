#pragma once

#include "Communication.hpp"
#include "IGraphical.hpp"
#include <memory>
#include <string>

namespace zappy {

    class Zappy {
        public:
            Zappy() = delete;
            Zappy(int port, std::string hostname);
            ~Zappy();
            void Run();

        private:
            Communication _commuication;
            std::unique_ptr<IGraphical> _graphical;
            bool _exit;

            void SocketLoop();
    };

}
