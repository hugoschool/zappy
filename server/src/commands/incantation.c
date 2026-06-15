#include "level.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>

bool command_incantation_check(server_t *server)
{
    if (level_up_possibility(server)) {
        dprintf(*CLIENT->fd, "Elevation underway\n");
        return true;
    }
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
    return false;
}

void command_incantation(server_t *server)
{
    if (level_up(server)) {
        dprintf(*CLIENT->fd, "Current level: %d\n", CLIENT->level);
    } else
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
}
