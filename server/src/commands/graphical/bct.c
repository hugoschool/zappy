#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"
#include "utils.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>

void command_graphic_bct_coordinates(server_t *server, int graphic_i, int x, int y)
{
    tile_t *tile = &server->world->tiles[ZW_POS(server->world->width, x, y)];

    dprintf(*CLIENT_I(graphic_i)->fd,
    "bct %d %d %d %d %d %d %d %d %d" ZMSG_END_SEQ,
        x, y,
        tile->stock.food,
        tile->stock.linemate,
        tile->stock.deraumere,
        tile->stock.sibur,
        tile->stock.mendiane,
        tile->stock.phiras,
        tile->stock.thystame
    );
}

void command_graphic_bct(server_t *server)
{
    string_vec_t *vec = string_split(CLIENT->command_str, CMDS_SPLIT);
    int x = -1;
    int y = -1;

    if (vec == NULL)
        return;
    x = atoi(vec->elems[1]);
    y = atoi(vec->elems[2]);
    string_vec_free(vec);
    if (x < 0 || x > (int)server->world->width
        || y < 0 || y > (int)server->world->height) {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_SBP);
        return;
    }
    command_graphic_bct_coordinates(server, server->index, x, y);
}
