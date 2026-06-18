#include "server.h"
#include "messages.h"
#include <stdio.h>

void command_graphic_seg_index(server_t *server, int graphic_i, const char *team_name)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "seg %s" ZMSG_END_SEQ, team_name);
}
