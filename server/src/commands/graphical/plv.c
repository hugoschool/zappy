#include "clients.h"
#include "commands.h"
#include "server.h"
#include "messages.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_graphic_plv(server_t *server)
{
    string_vec_t *vec = string_split(server->buffer, CMDS_SPLIT);
    int player_nb = -1;
    client_data_t *player;

    if (vec == NULL)
        return;
    player_nb = get_player_nb(vec->elems[1]);
    string_vec_free(vec);
    if (player_nb < 0 || player_nb >= (int)(server->players->amount)) {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_SBP);
        return;
    }
    player = PLAYER_I(player_nb);
    dprintf(*CLIENT->fd, "plv #%d %d" ZMSG_END_SEQ,
        player_nb,
        player->level
    );
}
