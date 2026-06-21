#ifndef ZAPPY_SERVER_CLIENTS_H_
    #define ZAPPY_SERVER_CLIENTS_H_

    #include "buffer.h"
    #include "teams.h"
    #include "stock.h"
    #include "world.h"
    #include <stdbool.h>
    #include <stddef.h>
    #include <time.h>

    // Use this macro when doing an iteration of all clients
    #define CLIENT_INITIAL_INDEX INITIAL_SOCKET_AMOUNT

    // Gets the current client
    #define CLIENT server->clients->elems[server->index]

    // Gets client at index i
    #define CLIENT_I(i) server->clients->elems[i]

    // ABS macro
    #define ABS(x) ((x < 0) ? x * -1 : x)

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

struct commands_s;

typedef struct {
    // Current step of the first step flow
    client_login_step_t current_step;
    // The current client a graphical client?
    bool is_graphical;
    // Client direction
    client_direction_t direction;
    // Level
    unsigned int level;
    // Stock of the client
    stock_t stock;
    // Player number
    size_t player_nb;

    // Buffer
    circular_buffer_t *buffer;
    // Command string currently being handled
    char *command_str;

    // Pointer to the associated team
    team_data_t *team;
    // Pointer to its struct pollfd file descriptor
    int *fd;
    // Pointer to the associated tile
    tile_t *tile;

    // Is the command running?
    bool is_command_running;
    // Start of the command execution
    struct timespec command_start;
    // The command in exectution
    struct commands_s *command;
    // The food available for consuption (-1 if the client cannot die)
    double food_freq_offset;
    // Food clock
    struct timespec food_clock;
} client_data_t;

client_data_t *client_data_init(int *fd);
void client_move_in_direction(client_data_t *data, world_t *world, client_direction_t direction);
int client_get_direction_number(client_data_t *data);
void client_data_free(client_data_t *data);

typedef struct {
    client_data_t **elems;
    size_t amount;
    size_t size;
} clients_t;

clients_t *clients_init(void);
void client_associate_team(clients_t *clients, int i, team_data_t *team);
size_t clients_get_amount_at_level(clients_t *clients, unsigned int level);
int clients_find_by_player_nb(clients_t *clients, size_t player_nb);
void clients_append(clients_t *clients, int *fd);
void clients_delete(clients_t *clients, int i);
void clients_free(clients_t *clients);
int client_get_shortest_direction_tile(client_data_t *source, client_data_t *destination, world_t *world);

#endif
