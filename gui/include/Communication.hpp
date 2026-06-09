#pragma once

#include "Socket.hpp"
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace zappy {

    class Communication {
        public:
            Communication() = delete;
            Communication(int port, std::string hostname);
            ~Communication();

            void SocketLoop();

        private:
            Socket _socket;

            std::map<std::string, std::function<void(std::vector<std::string>)>> _commands;
            void UpdateFd(int i);
            void ReadMessage();
            void ParseMessage(std::string msg);

            //Commands
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
            void welcome(std::vector<std::string> params);
    };

}
