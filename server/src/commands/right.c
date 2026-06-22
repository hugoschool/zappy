#include "commands.h"
#include "messages.h"
#include "server.h"

void command_right(server_t *server)
{
    // Correctly handle C's negative modulus
    // TIL: -90 % 360 = -90 in C but -90 % 360 = 270 in Python
    if (CLIENT->direction == 0)
        CLIENT->direction = 360;
    CLIENT->direction = (CLIENT->direction - 90) % 360;
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_ppo_index(server, i, CLIENT->player_nb);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
