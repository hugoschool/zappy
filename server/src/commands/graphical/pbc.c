#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_graphic_pbc_index(server_t *server, int graphic_i, int player_i, const char *element)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "pbc #%d %s" ZMSG_END_SEQ,
        player_i,
        element
    );
}
