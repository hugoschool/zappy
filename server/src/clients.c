#include "clients.h"
#include "dynamic_arrays.h"
#include "poller.h"
#include "server.h"
#include "stock.h"
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
    // No need to init that
    // data->command_start;
    data->command = NULL;
    return data;
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
    data->tile = &world->tiles[ZW_POS(world->width, new_x, new_y)];
}

void client_data_free(client_data_t *data)
{
    if (data == NULL)
        return;
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
