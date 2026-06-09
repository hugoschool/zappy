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
    // Command only works in graphical
    bool graphical_only;
} commands_t;

void command_graphic_msz(server_t *server);

static const commands_t cmds[] = {
    {
        .command = "msz",
        .function = &command_graphic_msz,
        .args_amount = 1,
        .graphical_only = true,
    },
    {.command = NULL, .function = NULL, .args_amount = 0, .graphical_only = false}
};

void commands_handler(server_t *server);

#endif
