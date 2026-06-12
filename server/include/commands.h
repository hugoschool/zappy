#ifndef ZAPPY_SERVER_COMMANDS_H_
    #define ZAPPY_SERVER_COMMANDS_H_

    #include "server.h"
    #include <unistd.h>

    #define CMDS_TEMP_BUFFER_SIZE 1024
    #define CMDS_SPLIT " "

typedef struct commands_s {
    const char *command;
    void (*function)(server_t *server);
    // Represents the amount of arguments the command can take.
    // A negative amount means the command is doing the handling of the arguments itself.
    // Ex: USER a takes in 1 argument
    const char args_amount;
    // Command only works in graphical
    bool graphical_only;
    // Time taken for the command execution, it needs to be divided by the server frequency (-1 for commands with no time limit).
    int time_limit;
    // Time limit for commands
    //  - Forward 7/f
    //  - Right 7/f
    //  - Left 7/f
    //  - Look 7/f
    //  - Inventory 1/f
    //  - Broadcast 7/f
    //  - Connect_nbr -1
    //  - Fork 42/f
    //  - Eject 7/f
    //  - death of a player -1 (not really a command)
    //  - Take <object> 7/f
    //  - Set <object> 7/f
    //  - Incantation 300/f
} commands_t;

// Client prototypes
void command_left(server_t *server);
void command_right(server_t *server);
void command_inventory(server_t *server);
void command_take(server_t *server);
void command_set(server_t *server);
void command_connect_nbr(server_t *server);
void command_fork(server_t *server);
void command_forward(server_t *server);

// Graphical prototypes
void command_graphic_msz(server_t *server);

static const commands_t cmds[] = {
    // Client
    {
        .command = "Left",
        .function = &command_left,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Right",
        .function = &command_right,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Inventory",
        .function = &command_inventory,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 1,
    },
    {
        .command = "Take",
        .function = &command_take,
        .args_amount = 1,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Set",
        .function = &command_set,
        .args_amount = 1,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Connect_nbr",
        .function = &command_connect_nbr,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = -1,
    },
    {
        .command = "Fork",
        .function = &command_fork,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 42,
    },
    {
        .command = "Forward",
        .function = &command_forward,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },
    // Graphical
    {
        .command = "msz",
        .function = &command_graphic_msz,
        .args_amount = 0,
        .graphical_only = true,
        .time_limit = -1,
    },
    {.command = NULL, .function = NULL, .args_amount = 0, .graphical_only = false, .time_limit = -1}
};

void commands_handler(server_t *server);

#endif
