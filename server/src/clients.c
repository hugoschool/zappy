#include "clients.h"
#include "buffer.h"
#include "dynamic_arrays.h"
#include "poller.h"
#include "stock.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

client_data_t *client_data_init(int *fd)
{
    client_data_t *data = malloc(sizeof(client_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    data->current_step = ENTER_TEAM_NAME;
    data->direction = RIGHT;
    stock_initialize_client(&data->stock);
    data->level = 1;
    data->is_graphical = false;
    data->fd = fd;
    data->team = NULL;
    data->tile = NULL;
    data->is_command_running = false;
    data->buffer = cb_init();
    if (data->buffer == NULL)
        return NULL;
    data->command_str = NULL;
    data->player_nb = -1;
    data->player_graphical_index = -1;
    // No need to init that
    // data->command_start;
    data->command = NULL;
    // Food variables init
    data->food_freq_offset = 0;
    timespec_get(&data->food_clock, TIME_UTC);
    return data;
}

void client_modify_command_str(client_data_t *data, char *str)
{
    if (data->command_str != NULL)
        free(data->command_str);
    data->command_str = str;
}

void client_move_in_direction(client_data_t *data, world_t *world, client_direction_t direction)
{
    unsigned int new_x = data->tile->x;
    unsigned int new_y = data->tile->y;

    switch (direction) {
        case RIGHT:
            if (new_x + 1 >= world->width)
                new_x = 0;
            else
                new_x++;
            break;
        case UP:
            if (new_y != 0)
                new_y--;
            else
                new_y = world->height - 1;
            break;
        case LEFT:
            if (new_x != 0)
                new_x--;
            else
                new_x = world->width - 1;
            break;
        case DOWN:
            if (new_y + 1 >= world->height)
                new_y = 0;
            else
                new_y++;
            break;
    }
    data->tile = &world->tiles[new_y][new_x];
}

// Used by graphical functions
int client_get_direction_number(client_data_t *data)
{
    switch (data->direction) {
        case UP:
            return 1;
        case RIGHT:
            return 2;
        case DOWN:
            return 3;
        case LEFT:
            return 4;
    }
    return -1;
}

void client_data_free(client_data_t *data)
{
    if (data == NULL)
        return;
    cb_free(data->buffer);
    free(data);
    data = NULL;
}

clients_t *clients_init(void)
{
    clients_t *clients = malloc(sizeof(clients_t));

    if (clients == NULL) {
        perror("malloc");
        exit(84);
    }
    DA_INIT(clients, client_data_t);
    clients->amount = INITIAL_SOCKET_AMOUNT;
    for (size_t i = 0; i < clients->amount; i++) {
        clients->elems[i] = client_data_init(NULL);
        // -1 food is for fake client
        clients->elems[i]->stock.food = -1;
    }
    return clients;
}

void clients_append(clients_t *clients, int *fd)
{
    if (clients == NULL)
        return;
    DA_APPEND(clients, client_data_init(fd));
}

void clients_delete(clients_t *clients, int i)
{
    if (clients == NULL ||
        (unsigned int)i >= clients->amount ||
        clients->elems[i] == NULL)
        return;
    client_data_free(clients->elems[i]);
    clients->elems[i] = clients->elems[clients->amount - 1];
    clients->amount--;
}

void client_associate_team(clients_t *clients, int i, team_data_t *team)
{
    if (clients == NULL ||
        (unsigned int)i >= clients->amount ||
        clients->elems[i] == NULL)
        return;
    clients->elems[i]->team = team;
}

size_t clients_get_amount_at_level(clients_t *clients, unsigned int level)
{
    size_t amount = 0;

    if (clients == NULL)
        return amount;
    for (size_t i = CLIENT_INITIAL_INDEX; i < clients->amount; i++) {
        if (clients->elems[i]->level == level)
            amount++;
    }
    return amount;
}

void clients_free(clients_t *clients)
{
    if (clients == NULL)
        return;
    DA_FREE(clients, client_data_free);
}

int clients_find_by_player_nb(clients_t *clients, size_t player_nb)
{
    for (size_t i = CLIENT_INITIAL_INDEX; i < clients->amount; i++) {
        if (clients->elems[i]->is_graphical == false && clients->elems[i]->player_nb == player_nb)
            return i;
    }
    return -1;
}

static int apply_client_orientation(int shortest_direction, client_direction_t client_direction)
{
    int discrepancy;

    switch (client_direction) {
        case UP:
            discrepancy = 0;
            break;
        case RIGHT:
            discrepancy = 2;
            break;
        case DOWN:
            discrepancy = 4;
            break;
        case LEFT:
            discrepancy = 6;
            break;
    }
    return ((shortest_direction + discrepancy) - 1) % 8 + 1;
}

int client_get_shortest_direction_tile(client_data_t *source, client_data_t *destination, world_t *world)
{
    // Orientation not depending on the source orientation
    int x_direction;
    int y_direction;

    // x
    long x_distance = (long)destination->tile->x - (long)source->tile->x;
    long opposite_x_distance = x_distance + ((x_distance < 0) ? world->width : -world->width);
    if (ABS(x_distance) < ABS(opposite_x_distance)) {
        x_direction = (x_distance < 0) ? 3 : 7;
    } else {
        x_direction = (opposite_x_distance < 0) ? 3 : 7;
    }

    // y
    long y_distance = (long)destination->tile->y - (long)source->tile->y;
    long opposite_y_distance = y_distance + ((y_distance < 0) ? world->height : -world->height);
    if (ABS(y_distance) < ABS(opposite_y_distance)) {
        y_direction = (y_distance < 0) ? 1 : 5;
    } else {
        y_direction = (opposite_y_distance < 0) ? 1 : 5;
    }

    if (source->tile->x == destination->tile->x && source->tile->y == destination->tile->y) {
        return 0;
    } else if (source->tile->x == destination->tile->x) {
        return apply_client_orientation(y_direction, source->direction);
    } else if (source->tile->y == destination->tile->y) {
        return apply_client_orientation(x_direction, source->direction);
    } else {
        // TODO do this better
        // 🤮
        // return apply_client_orientation((x_direction == 3) ? ((y_direction == 1) ? 2 : 4) : ((y_direction == 1) ? 8 : 6), source->direction);
        if (x_direction == 3) {
            if (y_direction == 1) {
                return apply_client_orientation(2, source->direction);
            } else {
                return apply_client_orientation(4, source->direction);
            }
        } else {
            if (y_direction == 1) {
                return apply_client_orientation(8, source->direction);
            } else {
                return apply_client_orientation(6, source->direction);
            }
        }
    }
}
