#include "clients.h"
#include "dynamic_arrays.h"
#include "poller.h"
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

void clients_free(clients_t *clients)
{
    if (clients == NULL)
        return;
    DA_FREE(clients, client_data_free);
}
