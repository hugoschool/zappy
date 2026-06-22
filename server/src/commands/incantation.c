#include "clients.h"
#include "commands.h"
#include "level.h"
#include "messages.h"
#include "server.h"
#include <stdio.h>

bool command_incantation_check(server_t *server)
{
    if (level_up_possibility(server)) {
        dprintf(*CLIENT->fd, "Elevation underway\n");
        for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
            if (CLIENT_I(i)->is_graphical == true) {
                // TODO: I think the incantation needs a change, apparently the player_nb in the subject
                // is the amount of the players that need to be incanting at the same time.
                // Therefore this is only a temporary array that needs to be reworked to work correctly
                // which is part of a bigger rework.
                int player_array[] = {CLIENT->player_nb};

                command_graphic_pic_index(server, i, CLIENT->tile->x, CLIENT->tile->y, CLIENT->level, player_array, 1);
            }
        }
        return true;
    }
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
    return false;
}

void command_incantation(server_t *server)
{
    bool success = false;

    if (level_up(server)) {
        dprintf(*CLIENT->fd, "Current level: %d\n", CLIENT->level);
        success = true;
    } else {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
        success = false;
    }
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_pie_index(server, i, CLIENT->tile->x, CLIENT->tile->y, success);
}
