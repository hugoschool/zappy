#include "server.h"
#include "messages.h"
#include <stdio.h>

void command_graphic_pdi_index(server_t *server, int graphic_i, int player_i)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "pdi #%d" ZMSG_END_SEQ, player_i);
}
