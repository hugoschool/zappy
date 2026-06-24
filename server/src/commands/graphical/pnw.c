#include "clients.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>

void command_graphic_pnw_index(server_t *server, size_t graphic_i, size_t player_i)
{
    client_data_t *client = PLAYER_I(player_i);

    dprintf(*CLIENT_I(graphic_i)->fd, "pnw #%d %d %d %d %d %s" ZMSG_END_SEQ,
        client->player_graphical_index, client->tile->x, client->tile->y,
        client_get_direction_number(client),
        client->level,
        client->team->name
    );
}
