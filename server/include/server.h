#ifndef ZAPPY_SERVER_SERVER_H_
    #define ZAPPY_SERVER_SERVER_H_

    #include "args.h"
    #include "clients.h"
    #include "players.h"
    #include "poller.h"
    #include "teams.h"
    #include "world.h"
    #include <stdbool.h>
    #include <netinet/in.h>

    #define DEFAULT_POLL_TIMEOUT 20 // milliseconds

// Socket
int socket_init(in_port_t port);

// Server
typedef struct {
    poller_t *poller;
    clients_t *clients;
    teams_t *teams;
    world_t *world;
    players_t *players;

    // CONTROL socket aka the main server socket
    int control_fd;
    // Handles the SIGINT (Ctrl + C)
    int signal_fd;
    // Represents the current client index that is being handled.
    unsigned int index;
    // Represents the frequency of commands excetution.
    int freq;
    // Reprensents the timeout parameter of the poll, it is calculated dynamically
    int poll_timeout;
} server_t;

bool zappy_server(args_t *args);
void server_free(server_t *server);
void client_quit(server_t *server);
void poll_handler(server_t *server, bool *running);

#endif
