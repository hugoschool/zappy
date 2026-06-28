#include "buffer.h"
#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"
#include "teams.h"
#include "world.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

    if (cfd == -1) {
        perror("accept");
        return;
    }
    poller_append(server->poller, cfd);
    clients_append(server->clients, cfd);
    WRITE_MESSAGE(cfd, ZMSG_WELCOME);
}

static void client_send_death_message(server_t *server)
{
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_pdi_index(server, i, CLIENT->player_index);
}

void client_quit(server_t *server)
{
    int fd = CLIENT->fd;

    if (fd != server->control_fd && fd != server->signal_fd) {
        if (close(fd) == -1)
            perror("close");
        if (CLIENT->is_graphical == false && CLIENT->current_step == LOGGED_IN) {
            client_send_death_message(server);
            players_delete(server->players, CLIENT->player_index);
        }
        poller_delete(server->poller, server->index);
        clients_delete(server->clients, server->index);
        server->index--;
    }
}

static void login_list_all_eggs(server_t *server, int graphic_i)
{
    eggs_t *eggs = NULL;

    for (unsigned int y = 0; y < server->world->height; y++) {
        for (unsigned int x = 0; x < server->world->width; x++) {
            eggs = server->world->tiles[y][x].eggs;
            if (eggs == NULL)
                continue;
            for (size_t i = 0; i < eggs->amount; i++) {
                command_graphic_enw_index(server, graphic_i, -1, eggs->elems[i], x, y);
            }
        }
    }
}

static bool client_login_graphic(server_t *server)
{
    CLIENT->is_graphical = true;
    CLIENT->current_step = LOGGED_IN;
    command_graphic_msz(server);
    command_graphic_sgt_index(server, server->index);
    for (size_t i = 0; i < server->players->amount; i++) {
        command_graphic_pnw_index(server, server->index, i);
        command_graphic_pin_index(server, server->index, i);
    }
    command_graphic_mct_index(server, server->index);
    command_graphic_tna_index(server, server->index);
    login_list_all_eggs(server, server->index);
    return true;
}

static bool client_login_normal(server_t *server)
{
    int team_index = teams_find_by_name(server->teams, CLIENT->command_str);

    if (team_index == -1 || TEAM_I(team_index)->clients == 0) {
        WRITE_MESSAGE(CLIENT->fd, ZMSG_KO);
        return true;
    }
    CLIENT->current_step = LOGGED_IN;
    TEAM_I(team_index)->clients--;
    client_associate_team(server->clients, server->index, TEAM_I(team_index));
    dprintf(CLIENT->fd, "%d" ZMSG_END_SEQ, TEAM_I(team_index)->clients);
    dprintf(CLIENT->fd, "%d %d" ZMSG_END_SEQ, server->world->width, server->world->height);
    CLIENT->tile = team_data_get_egg(CLIENT->team);
    if (CLIENT->tile == NULL) {
        CLIENT->current_step = ENTER_TEAM_NAME;
        return true;
    }
    int egg_id = eggs_consume_one(CLIENT->tile->eggs);
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_ebo_index(server, i, egg_id);
    players_append(server->players, CLIENT);
    CLIENT->player_index = server->players->amount - 1;
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
        if (CLIENT_I(i)->is_graphical == true) {
            command_graphic_pnw_index(server, i, CLIENT->player_index);
            command_graphic_pin_index(server, i, CLIENT->player_index);
        }
    }
    return true;
}

// Returns true if the client just logged in
static bool client_first_steps_handler(server_t *server)
{
    switch (CLIENT->current_step) {
        case ENTER_TEAM_NAME: {
            if (strcmp(CLIENT->command_str, TEAM_GRAPHIC_NAME) == 0)
                return client_login_graphic(server);
            else
                return client_login_normal(server);
        }
        case LOGGED_IN:
            return false;
    }
    return true;
}

void client_command_handler(server_t *server)
{
    if (CLIENT->is_command_running == true)
        return;
    CLIENT->command_str = cb_pop_delimiter(CLIENT->buffer);
    if (CLIENT->command_str == NULL)
        return;
    if (client_first_steps_handler(server) == false)
        commands_handler(server);
}

void client_buffer_handler(server_t *server)
{
    size_t read_i = 0;
    int fd = server->poller->elems[server->index].fd;
    ssize_t bytes_read = 0;
    char buffer[BUFFER_SIZE];

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0 && read_i == 0)
            return client_quit(server);
        buffer[bytes_read] = 0;
        read_i++;
        cb_push_buffer(CLIENT->buffer, buffer);
        if (bytes_read < BUFFER_SIZE - 1)
            break;
    }
    client_command_handler(server);
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
        client_buffer_handler(server);
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
