#include "poller.h"
#include "dynamic_arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/poll.h>

poller_t *poller_init(void)
{
    poller_t *poller = malloc(sizeof(poller_t));

    if (poller == NULL) {
        perror("malloc");
        exit(84);
    }
    DA_INIT(poller, struct pollfd);
    poller->amount = INITIAL_SOCKET_AMOUNT;
    if (poller->elems == NULL) {
        perror("calloc");
        exit(84);
    }
    return poller;
}

void poller_free(poller_t *poller)
{
    if (poller == NULL)
        return;
    free(poller->elems);
    free(poller);
}

static void poller_set_init_socket(poller_t *poller, int socket_fd)
{
    poller->elems[0].fd = socket_fd;
    poller->elems[0].events = POLLIN;
    poller->elems[0].revents = 0;
}

static void poller_set_signal_fd(poller_t *poller, int signal_fd)
{
    poller->elems[1].fd = signal_fd;
    poller->elems[1].events = POLLIN;
    poller->elems[1].revents = 0;
}

void poller_set_init_values(poller_t *poller, int socket_fd, int signal_fd)
{
    if (poller == NULL)
        return;
    poller_set_init_socket(poller, socket_fd);
    poller_set_signal_fd(poller, signal_fd);
}

void poller_append(poller_t *poller, int fd)
{
    if (poller == NULL)
        return;

    struct pollfd pollfd = {fd, POLLIN, 0};
    DA_APPEND(poller, pollfd);
}

void poller_delete(poller_t *poller, int i)
{
    if (poller == NULL)
        return;
    poller->elems[i] = poller->elems[poller->amount - 1];
    poller->amount--;
}
