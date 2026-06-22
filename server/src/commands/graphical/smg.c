#include "clients.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>

void command_graphic_smg_str(server_t *server, size_t graphic_i, const char *str)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "smg %s" ZMSG_END_SEQ, str);
}
