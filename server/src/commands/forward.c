#include "messages.h"
#include "server.h"
#include "world.h"

void command_forward(server_t *server)
{
    unsigned int new_x = CLIENT->tile->x;
    unsigned int new_y = CLIENT->tile->y;

    switch (CLIENT->direction) {
        case RIGHT:
            if (new_x + 1 >= server->world->width)
                new_x = 0;
            else
                new_x++;
            break;
        case UP:
            if (new_y != 0)
                new_y--;
            else
                new_y = server->world->height - 1;
            break;
        case LEFT:
            if (new_x != 0)
                new_x--;
            else
                new_x = server->world->width - 1;
            break;
        case DOWN:
            if (new_y + 1 >= server->world->height)
                new_y = 0;
            else
                new_y++;
            break;
    }
    CLIENT->tile = &server->world->tiles[ZW_POS(server->world->width, new_x, new_y)];
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
