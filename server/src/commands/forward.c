#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"

void command_forward(server_t *server)
{
    client_move_in_direction(CLIENT, server->world, CLIENT->direction);
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_ppo_index(server, i, CLIENT->player_nb);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
