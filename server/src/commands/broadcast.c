#include "commands.h"
#include "clients.h"
#include "messages.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void command_broadcast(server_t *server)
{
    if (string_split_amount(CLIENT->command_str, CMDS_SPLIT) <= 1) {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
        return;
    }

    const char *text = &CLIENT->command_str[strlen(CMDS_BROADCAST) + 1];
    int tile_nb = -1;

    for (size_t i = 0; i < server->players->amount; i++) {
        if (i != CLIENT->player_nb) {
            tile_nb = client_get_shortest_direction_tile(PLAYER_I(i), CLIENT, server->world);
            dprintf(*PLAYER_I(i)->fd, "message %d, %s" ZMSG_END_SEQ, tile_nb, text);
        }
    }
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_pbc_index(server, i, CLIENT->player_nb, text);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
