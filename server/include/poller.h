#ifndef ZAPPY_SERVER_POLLER_H_
    #define ZAPPY_SERVER_POLLER_H_

    #include <stddef.h>

// It is initially set to this amount for:
// - the initial control socket
// - the signal file descriptor handler.
#define INITIAL_SOCKET_AMOUNT 2

// Poller
typedef struct {
    struct pollfd *elems;
    size_t amount;
    size_t size;
} poller_t;

poller_t *poller_init(void);
void poller_fd_add(poller_t *poller, int fd);
void poller_fd_delete(poller_t *poller, int i);
void poller_set_init_values(poller_t *poller, int socket_fd, int signal_fd);
void poller_free(poller_t *poller);

#endif
