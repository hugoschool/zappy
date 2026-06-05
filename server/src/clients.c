#include "clients.h"
#include "dynamic_arrays.h"
#include <stdio.h>
#include <stdlib.h>

client_data_t *client_data_init(int *fd)
{
    client_data_t *data = malloc(sizeof(client_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    data->fd = fd;
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

void clients_free(clients_t *clients)
{
    if (clients == NULL)
        return;
    DA_FREE(clients, client_data_free);
}
