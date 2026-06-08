#include "commands.h"
#include "messages.h"
#include "server.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// TODO: refactor this function to match zappy specs
// Returns true if the command is valid and could stop the loop
static bool verify_command(server_t *server, int i)
{
    if (strncmp(server->buffer, cmds[i].command, strlen(cmds[i].command)) == 0) {
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
    write(*CLIENT->fd, ZMSG_KO, strlen(ZMSG_KO));
}
