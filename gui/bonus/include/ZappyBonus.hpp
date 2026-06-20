#pragma once

#include "GameplatEntitiesHolder.hpp"
#include "Map.hpp"
#include "PlayerCommunication.hpp"
#include "Protocol.hpp"
#include "RaylibBonus.hpp"
#include "SafeQueue.hpp"
#include <functional>
#include <string>
#include <thread>
#include <vector>

namespace zappy {
    class ZappyBonus {
        public:
            ZappyBonus() = delete;
            ZappyBonus(int port, std::string hostname);
            ~ZappyBonus();

            void loop();

        private:
            zappy::Map _map;

            GameplayEntitiesHolder _geh;

            SafeQueue<std::vector<std::string>> _commandsQueue;
            SafeQueue<std::string> _playerMovesQueue;

            bool _exit;

            int _timeUnit;

            Protocol _protocol;
            std::thread _protocolThread;

            PlayerCommunication _playerCommunication;
            std::thread _playerThread;

            std::map<std::string, std::function<void(std::vector<std::string>)>> _commands;

            std::vector<std::string> _teamsNames;

            RaylibBonus _graphical;

            void launchProtocol();
            void launchPlayerCommunication();



            // Commands:
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
