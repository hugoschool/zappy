#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void execute_command(server_t *server, int i)
{
    CLIENT->command = (struct commands_s *)&cmds[i];
    CLIENT->is_command_running = true;
    timespec_get(&CLIENT->command_start, TIME_UTC);
}

static void verify_check_command(server_t *server, int i)
{
    if (cmds[i].check != NULL) {
        if (cmds[i].check(server))
            execute_command(server, i);
    } else {
        execute_command(server, i);
    }
}

// Returns true if the command is valid and could stop the loop
static bool verify_command(server_t *server, int i)
{
    if (strncmp(CLIENT->command_str, cmds[i].command, strlen(cmds[i].command)) == 0) {
        if (cmds[i].graphical_only == true && CLIENT->is_graphical == false)
            return false;
        if (cmds[i].args_amount >= 0 &&
            cmds[i].args_amount + 1 != string_split_amount(CLIENT->command_str, CMDS_SPLIT))
            return false;
        verify_check_command(server, i);
        return true;
    }
    return false;
}

void commands_handler(server_t *server)
{
    for (int i = 0; cmds[i].command != NULL; i++) {
        if (verify_command(server, i))
            return;
    }
    if (CLIENT->is_graphical)
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_SUC);
    else
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
}
