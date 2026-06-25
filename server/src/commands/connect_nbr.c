#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_connect_nbr(server_t *server)
{
    dprintf(CLIENT->fd, "%d" ZMSG_END_SEQ, CLIENT->team->clients);
}
