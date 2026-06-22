#include "commands.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_graphic_enw_index(server_t *server, int graphic_i, int player_i, int egg_id, int x, int y)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "enw #%d #%d %d %d" ZMSG_END_SEQ, egg_id, player_i, x, y);
}
