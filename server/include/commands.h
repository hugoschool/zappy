#ifndef ZAPPY_SERVER_COMMANDS_H_
    #define ZAPPY_SERVER_COMMANDS_H_

    #include "server.h"
    #include <unistd.h>

    #define CMDS_TEMP_BUFFER_SIZE 1024
    #define CMDS_TEMP_BIG_BUFFER_SIZE 8192
    #define CMDS_SPLIT " "

typedef struct commands_s {
    const char *command;

    // A function that checks if the function is possible to be ran.
    bool (*check)(server_t *server);

    // The function to be executed
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
bool command_incantation_check(server_t *server);
void command_incantation(server_t *server);
void command_look(server_t *server);

// Graphical prototypes
void command_graphic_msz(server_t *server);

static const commands_t cmds[] = {
    // Client
    {
        .command = "Left",
        .check = NULL,
        .function = &command_left,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Right",
        .check = NULL,
        .function = &command_right,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Inventory",
        .check = NULL,
        .function = &command_inventory,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 1,
    },
    {
        .command = "Take",
        .check = NULL,
        .function = &command_take,
        .args_amount = 1,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Set",
        .check = NULL,
        .function = &command_set,
        .args_amount = 1,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Connect_nbr",
        .check = NULL,
        .function = &command_connect_nbr,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = -1,
    },
    {
        .command = "Fork",
        .check = NULL,
        .function = &command_fork,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 42,
    },
    {
        .command = "Forward",
        .check = NULL,
        .function = &command_forward,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = "Incantation",
        .check = &command_incantation_check,
        .function = &command_incantation,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 300,
    },
    {
        .command = "Look",
        .check = NULL,
        .function = &command_look,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },

    // Graphical
    {
        .command = "msz",
        .check = NULL,
        .function = &command_graphic_msz,
        .args_amount = 0,
        .graphical_only = true,
        .time_limit = -1,
    },

    // The last ending command
    {
        .command = NULL,
        .function = NULL,
        .args_amount = 0,
        .graphical_only = false
    }
};

void commands_handler(server_t *server);

#endif
