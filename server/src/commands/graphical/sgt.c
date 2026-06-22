#include "server.h"
#include "messages.h"
#include <stdio.h>

void command_graphic_sgt_index(server_t *server, int graphic_i)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "sgt %d" ZMSG_END_SEQ, server->freq);
}

void command_graphic_sgt(server_t *server)
{
    command_graphic_sgt_index(server, server->index);
}
