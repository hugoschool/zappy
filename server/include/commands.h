#ifndef ZAPPY_SERVER_COMMANDS_H_
    #define ZAPPY_SERVER_COMMANDS_H_

    #include "server.h"
    #include <unistd.h>

    #define CMDS_TEMP_ARRAY_SIZE 256
    #define CMDS_TEMP_BUFFER_SIZE 1024
    #define CMDS_TEMP_BIG_BUFFER_SIZE 8192
    #define CMDS_SPLIT " "

    #define CMDS_BROADCAST "Broadcast"

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
void command_eject(server_t *server);
void command_broadcast(server_t *server);
void command_death(server_t *server);

// Graphical prototypes
void command_graphic_msz(server_t *server);
void command_graphic_bct(server_t *server);
void command_graphic_mct(server_t *server);
void command_graphic_tna(server_t *server);
void command_graphic_ppo(server_t *server);
void command_graphic_plv(server_t *server);
void command_graphic_pin(server_t *server);
void command_graphic_sgt(server_t *server);
void command_graphic_sst(server_t *server);

// Graphical events, not actual commands
void command_graphic_bct_coordinates(server_t *server, int graphic_i, int x, int y);
void command_graphic_mct_index(server_t *server, int graphic_i);
void command_graphic_pnw_index(server_t *server, size_t graphic_i, size_t player_i);
void command_graphic_tna_index(server_t *server, int graphic_i);
void command_graphic_sgt_index(server_t *server, int graphic_i);
void command_graphic_smg_str(server_t *server, size_t graphic_i, const char *str);
void command_graphic_enw_index(server_t *server, int graphic_i, int player_i, int egg_id, int x, int y);
void command_graphic_ebo_index(server_t *server, int graphic_i, int egg_id);
void command_graphic_pex_index(server_t *server, int graphic_i, int player_i);
void command_graphic_pdr_index(server_t *server, int graphic_i, int player_i, const char *element);
void command_graphic_pgt_index(server_t *server, int graphic_i, int player_i, const char *element);
void command_graphic_pbc_index(server_t *server, int graphic_i, int player_i, const char *element);
void command_graphic_pfk_index(server_t *server, int graphic_i, int player_i);
void command_graphic_seg_index(server_t *server, int graphic_i, const char *team_name);
void command_graphic_edi_index(server_t *server, int graphic_i, int egg_id);
void command_graphic_pdi_index(server_t *server, int graphic_i, int player_i);
void command_graphic_pie_index(server_t *server, int graphic_i, int x, int y, bool result);
void command_graphic_pic_index(server_t *server, int graphic_i, int x, int y, int level, int *player_array, size_t player_array_amount);
void command_graphic_pin_index(server_t *server, int graphic_i, int player_i);
void command_graphic_ppo_index(server_t *server, int graphic_i, int player_i);
void command_graphic_plv_index(server_t *server, int graphic_i, int player_i);

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
    {
        .command = "Eject",
        .check = NULL,
        .function = &command_eject,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = 7,
    },
    {
        .command = CMDS_BROADCAST,
        .check = NULL,
        .function = &command_broadcast,
        .args_amount = -1,
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
    {
        .command = "bct",
        .check = NULL,
        .function = &command_graphic_bct,
        .args_amount = 2,
        .graphical_only = true,
        .time_limit = -1,
    },
    {
        .command = "mct",
        .check = NULL,
        .function = &command_graphic_mct,
        .args_amount = 0,
        .graphical_only = true,
        .time_limit = -1,
    },
    {
        .command = "tna",
        .check = NULL,
        .function = &command_graphic_tna,
        .args_amount = 0,
        .graphical_only = true,
        .time_limit = -1,
    },
    {
        .command = "ppo",
        .check = NULL,
        .function = &command_graphic_ppo,
        .args_amount = 1,
        .graphical_only = true,
        .time_limit = -1,
    },
    {
        .command = "plv",
        .check = NULL,
        .function = &command_graphic_plv,
        .args_amount = 1,
        .graphical_only = true,
        .time_limit = -1,
    },
    {
        .command = "pin",
        .check = NULL,
        .function = &command_graphic_pin,
        .args_amount = 1,
        .graphical_only = true,
        .time_limit = -1,
    },
    {
        .command = "sgt",
        .check = NULL,
        .function = &command_graphic_sgt,
        .args_amount = 0,
        .graphical_only = true,
        .time_limit = -1,
    },
    {
        .command = "sst",
        .check = NULL,
        .function = &command_graphic_sst,
        .args_amount = 1,
        .graphical_only = true,
        .time_limit = -1,
    },

    // The last ending command
    {
        .command = NULL,
        .check = NULL,
        .function = NULL,
        .args_amount = 0,
        .graphical_only = false,
        .time_limit = -1
    }
};

void commands_handler(server_t *server);

#endif
