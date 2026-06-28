#include "clients.h"
#include "buffer.h"
#include "dynamic_arrays.h"
#include "poller.h"
#include "stock.h"
#include "world.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

client_data_t *client_data_init(int fd)
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
    data->player_index = -1;
    data->player_graphical_index = -1;
    // No need to init that
    // data->command_start;
    data->command_freq_offset = 0.0;
    data->command = NULL;
    // Food variables init
    data->food_freq_offset = 0;
    data->is_frozen = false;
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
        clients->elems[i] = client_data_init(-1);
        // -1 food is for fake client
        clients->elems[i]->stock.food = -1;
    }
    return clients;
}

void clients_append(clients_t *clients, int fd)
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

size_t clients_get_amount_at_level_on_tile(clients_t *clients, tile_t *tile, unsigned int level)
{
    size_t amount = 0;

    if (clients == NULL)
        return amount;
    for (size_t i = CLIENT_INITIAL_INDEX; i < clients->amount; i++) {
        if (clients->elems[i]->level == level && clients->elems[i]->tile == tile)
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

int clients_find_by_player_index(clients_t *clients, size_t player_index)
{
    for (size_t i = CLIENT_INITIAL_INDEX; i < clients->amount; i++) {
        if (clients->elems[i]->is_graphical == false
            && clients->elems[i]->player_index == player_index)
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
    // Check the same tile
    if (source->tile->x == destination->tile->x && source->tile->y == destination->tile->y) {
        return 0;
    }

    // The shortest vec between up and down (infinite map handling)
    int shortest_vec_x;
    int shortest_vec_y;

    // The vector with witch we create the angle
    int vertical_vec_x = 0;
    int vertical_vec_y = -1;

    // x
    long vec_x = (long)destination->tile->x - (long)source->tile->x;
    long opposite_vec_x = vec_x + ((vec_x < 0) ? (long)world->width : -(long)world->width);

    printf("vec_x %ld, opposite_vec_x %ld\n", vec_x, opposite_vec_x);
    if (ABS(vec_x) < ABS(opposite_vec_x)) {
        shortest_vec_x = vec_x;
    } else {
        shortest_vec_x = opposite_vec_x;
    }

    // y
    long vec_y = (long)destination->tile->y - (long)source->tile->y;
    long opposite_vec_y = vec_y + ((vec_y < 0) ? (long)world->height : -(long)world->height);

    printf("vec_x %ld, opposite_vec_x %ld\n", vec_y, opposite_vec_y);
    if (ABS(vec_y) < ABS(opposite_vec_y)) {
        shortest_vec_y = vec_y;
    } else {
        shortest_vec_y = opposite_vec_y;
    }

    printf("from %d to %d\n", source->player_graphical_index, destination->player_graphical_index);
    printf("vecx %d, vecy %d\n", shortest_vec_x, shortest_vec_y);
    printf("vectical vecx %d, vectical vecy %d\n", vertical_vec_x, vertical_vec_y);

    double vec_scalar = (shortest_vec_x * vertical_vec_x) + (shortest_vec_y * vertical_vec_y);
    double vec_norm = sqrt(pow(shortest_vec_x, 2) + pow(shortest_vec_y, 2));
    double vertical_vec_norm = sqrt(pow(vertical_vec_x, 2) + pow(vertical_vec_y, 2));
    double angle = acos(vec_scalar / (vec_norm * vertical_vec_norm)) * 180.0 / M_PI;

    // reverse clock wise
    angle = (shortest_vec_x > 0) ? 360 - angle : angle;

    printf("angle: %f\n", angle);

    angle += 45.0 / 2.0;
    angle = (angle < 0) ? angle + 360 : angle;

    printf("modified angle: %f\n", angle);

    int direction = (int)angle / 45 + 1;
    printf("before client orientation applied direction %d\n", direction);

    return apply_client_orientation(direction, source->direction); 
}

void client_level_up(client_data_t *client)
{
    client->level++;
    if (client->level == 8) {
        client->team->max_nb_player_lvl_8 += 1;
    }
}
