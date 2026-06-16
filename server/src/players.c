#include "dynamic_arrays.h"
#include "players.h"
#include <stdlib.h>

players_t *players_init(void)
{
    players_t *players = malloc(sizeof(players_t));

    if (players == NULL)
        return NULL;
    DA_INIT(players, client_data_t *);
    if (players->elems == NULL)
        return NULL;
    return players;
}

void players_append(players_t *players, client_data_t *client)
{
    DA_APPEND(players, client);
}

void players_free(players_t *players)
{
    free(players->elems);
    free(players);
}
