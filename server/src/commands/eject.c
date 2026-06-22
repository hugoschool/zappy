#include "commands.h"
#include "clients.h"
#include "messages.h"
#include "server.h"
#include "world.h"
#include <stdio.h>

static void send_graphical_move(server_t *server, int player_i)
{
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_ppo_index(server, i, player_i);
}

void command_eject(server_t *server)
{
    int tile_nb = -1;

    for (size_t i = 0; i < server->players->amount; i++) {
        if (i != CLIENT->player_nb && PLAYER_I(i)->tile == CLIENT->tile) {
            client_move_in_direction(PLAYER_I(i), server->world, CLIENT->direction);
            send_graphical_move(server, PLAYER_I(i)->player_nb);
            tile_nb = client_get_shortest_direction_tile(PLAYER_I(i), CLIENT, server->world);
            dprintf(*PLAYER_I(i)->fd, "eject: %d" ZMSG_END_SEQ, tile_nb);
        }
    }
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_pex_index(server, i, CLIENT->player_nb);
    tile_destroy_eggs(CLIENT->tile, server->world);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
