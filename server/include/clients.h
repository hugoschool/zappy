#ifndef ZAPPY_SERVER_CLIENTS_H_
    #define ZAPPY_SERVER_CLIENTS_H_

    #include "teams.h"
    #include "stock.h"
    #include "world.h"
    #include <stdbool.h>
    #include <stddef.h>

    // Gets the current client
    #define CLIENT server->clients->elems[server->index]

typedef enum {
    // Waiting for team name to be entered
    ENTER_TEAM_NAME,
    // Team name was entered and client is now playing
    LOGGED_IN,
} client_login_step_t;

typedef enum {
    RIGHT = 0,  // 0 rad
    UP = 90,    // pi/2 rad
    LEFT = 180, // pi
    DOWN = 270, // 3*pi/2 rad
} client_direction_t;

typedef struct {
    // Current step of the first step flow
    client_login_step_t current_step;
    // The current client a graphical client?
    bool is_graphical;
    // Client direction
    client_direction_t direction;
    // TODO: level
    // Stock of the client
    stock_t stock;
    // Pointer to the associated team
    team_data_t *team;
    // Pointer to its struct pollfd file descriptor
    int *fd;
    // Pointer to the associated tile
    tile_t *tile;
} client_data_t;

client_data_t *client_data_init(int *fd);
void client_data_free(client_data_t *data);

typedef struct {
    client_data_t **elems;
    size_t amount;
    size_t size;
} clients_t;

clients_t *clients_init(void);
void client_associate_team(clients_t *clients, int i, team_data_t *team);
void clients_append(clients_t *clients, int *fd);
void clients_delete(clients_t *clients, int i);
void clients_free(clients_t *clients);

#endif
