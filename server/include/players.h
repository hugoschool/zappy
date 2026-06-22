#ifndef ZAPPY_SERVER_PLAYERS_H_
    #define ZAPPY_SERVER_PLAYERS_H_

    #include "clients.h"
    #include <stdbool.h>
    #include <stddef.h>

    // Gets player at index i
    #define PLAYER_I(i) server->players->elems[i]

typedef struct {
    client_data_t **elems;
    size_t amount;
    size_t size;
} players_t;

players_t *players_init(void);
void players_append(players_t *players, client_data_t *client);
void players_free(players_t *players);
void players_delete(players_t *players, int i);

#endif
