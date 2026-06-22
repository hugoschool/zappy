#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_graphic_pex_index(server_t *server, int graphic_i, int player_i)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "pex #%d" ZMSG_END_SEQ, player_i);
}
