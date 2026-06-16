#include "clients.h"
#include "commands.h"
#include "server.h"
#include "messages.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_graphic_ppo(server_t *server)
{
    string_vec_t *vec = string_split(server->buffer, CMDS_SPLIT);
    int player_nb = -1;
    client_data_t *player;

    if (vec == NULL || strlen(vec->elems[1]) < 2)
        return;
    if (vec->elems[1][0] != '#') {
        string_vec_free(vec);
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_SBP);
        return;
    }
    player_nb = atoi(&vec->elems[1][1]);
    string_vec_free(vec);
    if (player_nb < 0 || player_nb >= (int)(server->players->amount)) {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_SBP);
        return;
    }
    player = PLAYER_I(player_nb);
    dprintf(*CLIENT->fd, "ppo #%d %d %d %d" ZMSG_END_SEQ,
        player_nb,
        player->tile->x, player->tile->y,
        client_get_direction_number(player)
    );
}
