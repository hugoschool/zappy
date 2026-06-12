#pragma once

#include "IGraphical.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Protocol.hpp"
#include "SafeQueue.hpp"
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace zappy {

    class Zappy {
        public:
            Zappy() = delete;
            Zappy(int port, std::string hostname);
            ~Zappy();
            void loop();

        private:
            zappy::Map _map;
            SafeQueue<std::vector<std::string>> _safeQueue;
            bool _exit;
            int _timeUnit;
            Protocol _protocol;
            std::unique_ptr<IGraphical> _graphical;
            std::thread _protocolThread;

            std::map<std::string, std::function<void(std::vector<std::string>)>> _commands;

            std::vector<std::string> _teamsNames;
            std::map<int, PlayerInfo> _players;

            void launchProtocol();

            std::queue<std::pair<int, std::string>> _broadCast;


            // Commandes
            void msz(std::vector<std::string> params);
            void bct(std::vector<std::string> params);
            void tna(std::vector<std::string> params);
            void pnw(std::vector<std::string> params);
            void ppo(std::vector<std::string> params);
            void plv(std::vector<std::string> params);
            void pin(std::vector<std::string> params);
            void pex(std::vector<std::string> params);
            void pbc(std::vector<std::string> params);
            void pic(std::vector<std::string> params);
            void pie(std::vector<std::string> params);
            void pfk(std::vector<std::string> params);
            void pdr(std::vector<std::string> params);
            void pgt(std::vector<std::string> params);
            void pdi(std::vector<std::string> params);
            void enw(std::vector<std::string> params);
            void ebo(std::vector<std::string> params);
            void edi(std::vector<std::string> params);
            void sgt(std::vector<std::string> params);
            void sst(std::vector<std::string> params);
            void seg(std::vector<std::string> params);
            void smg(std::vector<std::string> params);
            void suc(std::vector<std::string> params);
            void sbp(std::vector<std::string> params);

    };

}
