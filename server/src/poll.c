#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <sys/signalfd.h>
#include <sys/socket.h>
#include <unistd.h>

void new_client_handler(server_t *server)
{
    struct sockaddr_in caddr;
    socklen_t caddrl = sizeof(caddr);
    int cfd = accept(server->control_fd, (struct sockaddr *) &caddr, &caddrl);
    int *cfdr = NULL;

    if (cfd == -1) {
        perror("accept");
        return;
    }
    poller_fd_add(server->poller, cfd);
    cfdr = &server->poller->elems[server->poller->amount - 1].fd;
    clients_append(server->clients, cfdr);
    write(*cfdr, ZMSG_WELCOME, strlen(ZMSG_WELCOME));
}

void client_quit(server_t *server)
{
    int fd = *CLIENT->fd;

    if (fd != server->control_fd && fd != server->signal_fd) {
        if (close(fd) == -1)
            perror("close");
        poller_fd_delete(server->poller, server->index);
        clients_delete(server->clients, server->index);
        server->index--;
    }
}

// Returns true if the client just logged in
static bool client_first_steps_handler(server_t *server)
{
    switch (CLIENT->current_step) {
        case ENTER_TEAM_NAME: {
            int team_index = teams_find_by_name(server->teams, server->buffer);

            if (team_index == -1 || server->teams->elems[team_index]->clients == 0) {
                write(*CLIENT->fd, ZMSG_KO, strlen(ZMSG_KO));
                return true;
            }
            CLIENT->current_step = LOGGED_IN;
            server->teams->elems[team_index]->clients--;
            dprintf(*CLIENT->fd, "%d" ZMSG_END_SEQ, server->teams->elems[team_index]->clients);
            dprintf(*CLIENT->fd, "%d %d" ZMSG_END_SEQ, server->world->x, server->world->y);
            return true;
        }
        case LOGGED_IN:
            return false;
    }
    return true;
}

void client_handler(server_t *server)
{
    size_t read_i = 0;
    int fd = server->poller->elems[server->index].fd;
    ssize_t bytes_read = 0;
    char buffer[BUFFER_SIZE + 1];

    while (true) {
        memset(buffer, 0, BUFFER_SIZE + 1);
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0 && read_i == 0)
            return client_quit(server);
        buffer[bytes_read - 1] = 0;
        if (bytes_read < BUFFER_SIZE)
            break;
        read_i++;
    }
    server->buffer = buffer;
    if (client_first_steps_handler(server) == false)
        commands_handler(server);
}

static void signalfd_handler(bool *running)
{
    *running = false;
}

static void handle_pollin_events(server_t *server, bool *running)
{
    if (server->poller->elems[server->index].fd == server->control_fd)
        new_client_handler(server);
    else if (server->poller->elems[server->index].fd == server->signal_fd)
        signalfd_handler(running);
    else
        client_handler(server);
}

void poll_handler(server_t *server, bool *running)
{
    for (server->index = 0;
        server->index < server->poller->amount;
        server->index++) {
        if (server->poller->elems[server->index].revents & POLLIN) {
            handle_pollin_events(server, running);
        }
    }
}
