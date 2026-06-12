#include "messages.h"
#include "server.h"

void command_right(server_t *server)
{
    // Correctly handle C's negative modulus
    // TIL: -90 % 360 = -90 in C but -90 % 360 = 270 in Python
    if (CLIENT->direction == 0)
        CLIENT->direction = 360;
    CLIENT->direction = (CLIENT->direction - 90) % 360;
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
