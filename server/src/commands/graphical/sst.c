#include "commands.h"
#include "server.h"
#include "messages.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void command_graphic_sst(server_t *server)
{
    string_vec_t *vec = string_split(server->buffer, CMDS_SPLIT);
    int new_freq = -1;

    if (vec == NULL)
        return;
    new_freq = atoi(vec->elems[1]);
    string_vec_free(vec);
    if (new_freq <= 0) {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_SBP);
        return;
    }
    server->freq = new_freq;
    dprintf(*CLIENT->fd, "sst %d" ZMSG_END_SEQ, server->freq);
}
