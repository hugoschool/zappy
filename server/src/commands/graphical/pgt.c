#include "messages.h"
#include "server.h"
#include "stock.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void command_graphic_pgt_index(server_t *server, int graphic_i, int player_i, const char *element)
{
    dprintf(*CLIENT_I(graphic_i)->fd, "pgt #%d %d" ZMSG_END_SEQ,
        PLAYER_I(player_i)->player_graphical_index,
        stock_get_element_id(element)
    );
}
