#include "clients.h"
#include "commands.h"
#include "server.h"
#include "messages.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_graphic_ppo_index(server_t *server, int graphic_i, int player_i)
{
    client_data_t *player = PLAYER_I(player_i);

    dprintf(*CLIENT_I(graphic_i)->fd, "ppo #%d %d %d %d" ZMSG_END_SEQ,
        player_i,
        player->tile->x, player->tile->y,
        client_get_direction_number(player)
    );
}

void command_graphic_ppo(server_t *server)
{
    string_vec_t *vec = string_split(server->buffer, CMDS_SPLIT);
    int player_nb = -1;

    if (vec == NULL)
        return;
    player_nb = get_player_nb(vec->elems[1]);
    string_vec_free(vec);
    if (player_nb < 0 || player_nb >= (int)(server->players->amount)) {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_SBP);
        return;
    }
    command_graphic_ppo_index(server, server->index, player_nb);
}
