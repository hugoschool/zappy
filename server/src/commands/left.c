#include "messages.h"
#include "server.h"

void command_left(server_t *server)
{
    CLIENT->direction = (CLIENT->direction + 90) % 360;
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
