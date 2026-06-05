#ifndef ZAPPY_SERVER_CLIENTS_H_
    #define ZAPPY_SERVER_CLIENTS_H_

    #include <stddef.h>

    // Gets the current client
    #define CLIENT server->clients->elems[server->index]

// Clients
typedef struct {
    // Pointer to its struct pollfd file descriptor
    int *fd;
} client_data_t;

client_data_t *client_data_init(int *fd);
void client_data_free(client_data_t *data);

typedef struct {
    client_data_t **elems;
    size_t amount;
    size_t size;
} clients_t;

clients_t *clients_init(void);
void clients_append(clients_t *clients, int *fd);
void clients_delete(clients_t *clients, int i);
void clients_free(clients_t *clients);

#endif
