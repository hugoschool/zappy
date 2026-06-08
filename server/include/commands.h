#ifndef ZAPPY_SERVER_COMMANDS_H_
    #define ZAPPY_SERVER_COMMANDS_H_

    #include "server.h"
    #include <unistd.h>

typedef struct {
    const char *command;
    void (*function)(server_t *server);
    // Represents the amount of arguments the command can take.
    // A negative amount means the command is doing the handling of the arguments itself.
    // Ex: USER a takes in 1 argument
    const char args_amount;
} commands_t;

void command_noop(server_t *server);

static const commands_t cmds[] = {
    // TODO: remove once actual commands are present
    //
    // {
    //     .command = "NOOP",
    //     .function = &command_noop,
    //     .args_amount = 1,
    // },
    {.command = NULL, .function = NULL, .args_amount = 0}
};

void commands_handler(server_t *server);

#endif
