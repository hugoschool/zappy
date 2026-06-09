#pragma once

#include "Communication.hpp"
#include "IGraphical.hpp"
#include "Map.hpp"
#include <memory>
#include <string>
#include <thread>

namespace zappy {

    class Zappy {
        public:
            Zappy() = delete;
            Zappy(int port, std::string hostname);
            ~Zappy();
            void Run();

        private:
            zappy::Map _map;
            bool _exit;
            Communication _commuication;
            std::unique_ptr<IGraphical> _graphical;
            std::thread _communicationThread;

            void LaunchSocket();
    };

}
