#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_graphic_pfk_index(server_t *server, int graphic_i, int player_i)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "pfk #%d" ZMSG_END_SEQ, PLAYER_I(player_i)->player_graphical_index);
}
