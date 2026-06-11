#include "commands.h"
#include "messages.h"
#include "server.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// TODO: refactor this function to match zappy specs
// Returns true if the command is valid and could stop the loop
static bool verify_command(server_t *server, int i)
{
    if (strncmp(server->buffer, cmds[i].command, strlen(cmds[i].command)) == 0) {
        if (cmds[i].graphical_only == true && CLIENT->is_graphical == false)
            return false;
        if (cmds[i].args_amount >= 0 &&
            cmds[i].args_amount + 1 != string_split_amount(server->buffer, CMDS_SPLIT))
            return false;
        cmds[i].function(server);
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
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
}
