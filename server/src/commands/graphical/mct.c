#include "commands.h"
#include "server.h"
#include "world.h"

void command_graphic_mct_index(server_t *server, int graphic_i)
{
    for (unsigned int y = 0; y < server->world->height; y++) {
        for (unsigned int x = 0; x < server->world->width; x++)
            command_graphic_bct_coordinates(server, graphic_i, x, y);
    }
}

void command_graphic_mct(server_t *server)
{
    command_graphic_mct_index(server, server->index);
}
