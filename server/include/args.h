#ifndef ZAPPY_SERVER_ARGS_H_
    #define ZAPPY_SERVER_ARGS_H_

    #include <stdbool.h>
    #include <stddef.h>

    #define OPT_ARGUMENTS "pxyn:cf"

typedef struct {
    char **elems;
    size_t amount;
    size_t size;
} args_team_names_t;

typedef struct {
    // Server port
    int port;

    // Width and height of the world
    int x;
    int y;

    // Max clients amount
    int clients;

    // Frequency
    int freq;

    // Name of the teams
    args_team_names_t *names;

    // Validity of args
    bool valid;
} args_t;

args_t *parse_args(int argc, char *argv[]);
void args_free(args_t *args);

#endif
