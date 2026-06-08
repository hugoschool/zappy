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

            std::map<std::string, std::function<void(Communication *, std::vector<std::string>)>> _commands;
            void UpdateFd(int i);
            void ReadMessage();
            void ParseMessage(std::string msg);

            //Commands
            static void msz(Communication *, std::vector<std::string> params);
            static void bct(Communication *, std::vector<std::string> params);
            static void tna(Communication *, std::vector<std::string> params);
            static void pnw(Communication *, std::vector<std::string> params);
            static void ppo(Communication *, std::vector<std::string> params);
            static void plv(Communication *, std::vector<std::string> params);
            static void pin(Communication *, std::vector<std::string> params);
            static void pex(Communication *, std::vector<std::string> params);
            static void pbc(Communication *, std::vector<std::string> params);
            static void pic(Communication *, std::vector<std::string> params);
            static void pie(Communication *, std::vector<std::string> params);
            static void pfk(Communication *, std::vector<std::string> params);
            static void pdr(Communication *, std::vector<std::string> params);
            static void pgt(Communication *, std::vector<std::string> params);
            static void pdi(Communication *, std::vector<std::string> params);
            static void enw(Communication *, std::vector<std::string> params);
            static void ebo(Communication *, std::vector<std::string> params);
            static void edi(Communication *, std::vector<std::string> params);
            static void sgt(Communication *, std::vector<std::string> params);
            static void sst(Communication *, std::vector<std::string> params);
            static void seg(Communication *, std::vector<std::string> params);
            static void smg(Communication *, std::vector<std::string> params);
            static void suc(Communication *, std::vector<std::string> params);
            static void sbp(Communication *, std::vector<std::string> params);
    };

}
