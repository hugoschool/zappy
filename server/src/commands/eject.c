#include "commands.h"
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
    for (size_t i = 0; i < server->clients->amount; i++)
        if (server->clients->elems[i]->is_graphical == true)
            command_graphic_pex_index(server, i, CLIENT->player_nb);
    tile_destroy_eggs(CLIENT->tile, server->world);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
