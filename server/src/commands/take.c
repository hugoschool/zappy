#include "messages.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>

void command_take(server_t *server)
{
    string_vec_t *vec = string_split(server->buffer, " ");
    char *element = NULL;

    if (vec == NULL || vec->amount < 2)
        return;
    element = vec->elems[1];
    if (stock_exchange(&CLIENT->tile->stock, &CLIENT->stock, element)) {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
    } else {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
    }
    string_vec_free(vec);
}
