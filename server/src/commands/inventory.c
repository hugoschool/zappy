#include "commands.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>

void command_inventory(server_t *server)
{
    char buffer[CMDS_TEMP_BUFFER_SIZE] = {0};

    snprintf(buffer, CMDS_TEMP_BUFFER_SIZE,
    "[ "
        "food %u, "
        "linemate %u, "
        "deraumere %u, "
        "sibur %u, "
        "mendiane %u, "
        "phiras %u, "
        "thystame %u"
    " ]",
    CLIENT->stock.food,
    CLIENT->stock.linemate,
    CLIENT->stock.deraumere,
    CLIENT->stock.sibur,
    CLIENT->stock.mendiane,
    CLIENT->stock.phiras,
    CLIENT->stock.thystame);
    dprintf(*CLIENT->fd, "%s" ZMSG_END_SEQ, buffer);
}
