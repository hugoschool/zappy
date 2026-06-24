#include "messages.h"
#include "players.h"
#include "server.h"
#include <stddef.h>
#include <stdio.h>

void command_graphic_enw_index(server_t *server, int graphic_i, int player_i, int egg_id, int x, int y)
{
    if (player_i == -1) {
        dprintf(*CLIENT_I(graphic_i)->fd, "enw #%d #%d %d %d" ZMSG_END_SEQ, egg_id, player_i, x, y);
    } else {
        dprintf(*CLIENT_I(graphic_i)->fd, "enw #%d #%d %d %d" ZMSG_END_SEQ, egg_id, PLAYER_I(player_i)->player_graphical_index, x, y);
    }
}
