#include "clients.h"
#include "messages.h"
#include "server.h"

void command_forward(server_t *server)
{
    client_move_in_direction(CLIENT, server->world, CLIENT->direction);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
