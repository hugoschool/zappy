#include "commands.h"
#include "messages.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>

void command_set(server_t *server)
{
    string_vec_t *vec = string_split(CLIENT->command_str, CMDS_SPLIT);
    char *element = NULL;

    if (vec == NULL || vec->amount < 2)
        return;
    element = vec->elems[1];
    if (stock_exchange(&CLIENT->stock, &CLIENT->tile->stock, element)) {
        for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
            if (CLIENT_I(i)->is_graphical == true) {
                command_graphic_pdr_index(server, i, CLIENT->player_nb, element);
                command_graphic_bct_coordinates(server, i, CLIENT->tile->x, CLIENT->tile->y);
                command_graphic_pin_index(server, i, CLIENT->player_nb);
            }
        }
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
    } else {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
    }
    string_vec_free(vec);
}
