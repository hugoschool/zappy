#include "commands.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_graphic_ebo_index(server_t *server, int graphic_i, int egg_id)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "ebo #%d" ZMSG_END_SEQ, egg_id);
}
