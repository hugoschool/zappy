#include "server.h"
#include "messages.h"
#include <stdio.h>

void command_graphic_edi_index(server_t *server, int graphic_i, int egg_id)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "edi %d" ZMSG_END_SEQ, egg_id);
}
