#include "server.h"
#include "messages.h"
#include <stdio.h>

void command_graphic_msz(server_t *server)
{
    dprintf(CLIENT->fd, "msz %d %d" ZMSG_END_SEQ, server->world->width, server->world->height);
}
