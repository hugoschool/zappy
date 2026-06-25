#include "players.h"
#include "server.h"
#include "messages.h"
#include <stdio.h>

void command_graphic_pdi_index(server_t *server, int graphic_i, int player_i)
{
    // TODO verfiy this
    // got a valgrind error when triyng to test my widn conditions (invalid read of size 4 and 8)
    // when ^C the AI
    printf("%d\n", PLAYER_I(player_i)->player_graphical_index);
    dprintf(CLIENT_I(graphic_i)->fd, "pdi #%d" ZMSG_END_SEQ, PLAYER_I(player_i)->player_graphical_index);
}
