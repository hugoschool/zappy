#include "clients.h"
#include "messages.h"
#include "server.h"
#include "world.h"

void command_eject(server_t *server)
{
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
        if (i != server->index && CLIENT_I(i)->tile == CLIENT->tile) {
            client_move_in_direction(CLIENT_I(i), server->world, CLIENT->direction);
            // TODO: Send message to these clients
        }
    }
    tile_destroy_eggs(CLIENT->tile, server->world);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
