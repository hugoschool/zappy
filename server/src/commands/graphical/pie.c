#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_graphic_pie_index(server_t *server, int graphic_i, int x, int y, bool result)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "pie %d %d %d" ZMSG_END_SEQ, x, y, result);
}
