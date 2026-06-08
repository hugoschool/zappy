#include "server.h"
#include "args.h"
#include "teams.h"
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>

static void server_append_teams(server_t *server, args_t *args)
{
    for (size_t i = 0; i < args->names->amount; i++) {
        teams_append(server->teams, args->names->elems[i]);
    }
}

static server_t *server_init(args_t *args)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL) {
        perror("malloc");
        return NULL;
    }
    server->poller = poller_init();
    server->clients = clients_init();
    server->teams = teams_init(args->clients);
    if (server->poller == NULL || server->clients == NULL || server->teams == NULL) {
        free(server);
        return NULL;
    }
    server->control_fd = -1;
    server->signal_fd = -1;
    server_append_teams(server, args);
    return server;
}

void server_free(server_t *server)
{
    if (server == NULL)
        return;
    if (server->poller)
        poller_free(server->poller);
    if (server->clients)
        clients_free(server->clients);
    if (server->teams)
        teams_free(server->teams);
    free(server);
}

static void server_loop(server_t *server)
{
    int result = 0;
    bool running = true;

    while (running) {
        result = poll(server->poller->elems, server->poller->amount, -1);
        if (result == -1) {
            perror("poll");
            break;
        }
        poll_handler(server, &running);
    }
}

static int create_signalfd(void)
{
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
        return -1;
    return signalfd(-1, &mask, 0);
}

bool zappy_server(args_t *args)
{
    server_t *server = server_init(args);

    if (server == NULL)
        return false;
    server->control_fd = socket_init(args->port);
    server->signal_fd = create_signalfd();
    if (server->control_fd == -1 || server->signal_fd == -1) {
        server_free(server);
        return false;
    }
    poller_set_init_values(server->poller, server->control_fd,
        server->signal_fd);
    printf("Server launched!\n");
    server_loop(server);
    printf("Shutting down server\n");
    server_free(server);
    return true;
}
