#include "server.h"
#include "messages.h"
#include <stdio.h>

void command_graphic_tna_index(server_t *server, int graphic_i)
{
    for (size_t i = 0; i < server->teams->amount; i++) {
        dprintf(*CLIENT_I(graphic_i)->fd, "tna %s" ZMSG_END_SEQ, server->teams->elems[i]->name);
    }
}

void command_graphic_tna(server_t *server)
{
    command_graphic_tna_index(server, server->index);
}
