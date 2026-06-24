#include "dynamic_arrays.h"
#include "players.h"
#include <stddef.h>
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
    static size_t graphical_index = 0;

    client->player_graphical_index = graphical_index;
    DA_APPEND(players, client);

    graphical_index += 1;
}

void players_free(players_t *players)
{
    free(players->elems);
    free(players);
}

void players_delete(players_t *players, int i)
{
    if (players == NULL ||
        (unsigned int)i >= players->amount ||
        players->elems[i] == NULL)
        return;
    players->elems[players->amount - 1]->player_nb = i;
    players->elems[i] = players->elems[players->amount - 1];
    players->amount--;
}
