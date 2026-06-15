#include "commands.h"
#include "server.h"
#include "world.h"

void command_graphic_mct(server_t *server)
{
    for (unsigned int y = 0; y < server->world->height; y++) {
        for (unsigned int x = 0; x < server->world->width; x++)
            command_graphic_bct_coordinates(server, server->index, x, y);
    }
}
