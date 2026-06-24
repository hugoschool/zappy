#include "clients.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>

void command_death(server_t *server)
{
    dprintf(*CLIENT->fd, "dead" ZMSG_END_SEQ);
    client_quit(server);
}
