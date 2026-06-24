#include "clients.h"
#include "commands.h"
#include "frequency.h"
#include "level.h"
#include "messages.h"
#include "server.h"
#include <stddef.h>
#include <stdio.h>
#include <time.h>

bool command_incantation_check(server_t *server)
{
    if (level_up_possibility(server)) {
        int player_array[CMDS_TEMP_BUFFER_SIZE] = {0};
        size_t player_array_amount = 0;

        for (size_t i = 0; i < server->players->amount; i++) {
            if (PLAYER_I(i)->tile != CLIENT->tile || PLAYER_I(i)->level != CLIENT->level)
                continue;
            if (player_array_amount >= CMDS_TEMP_ARRAY_SIZE)
                break;
            PLAYER_I(i)->is_frozen = true;
            PLAYER_I(i)->command_freq_offset = calculate_time_elapsed(PLAYER_I(i)->command_start);
            dprintf(*PLAYER_I(i)->fd, "Elevation underway\n");
            player_array[player_array_amount] = i;
            player_array_amount++;
        }

        // Mark player as not frozen, as it is the one who initiated the incantation
        CLIENT->is_frozen = false;

        for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
            if (CLIENT_I(i)->is_graphical == true) {
                command_graphic_pic_index(server, i, CLIENT->tile->x, CLIENT->tile->y, CLIENT->level, player_array, player_array_amount);
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
        for (size_t i = 0; i < server->players->amount; i++) {
            if (PLAYER_I(i)->tile != CLIENT->tile || (PLAYER_I(i)->is_frozen == false && i != CLIENT->player_nb))
                continue;
            PLAYER_I(i)->is_frozen = false;
            timespec_get(&PLAYER_I(i)->command_start, TIME_UTC);
            dprintf(*PLAYER_I(i)->fd, "Current level: %d\n", CLIENT->level);
        }
        success = true;
    } else {
        WRITE_MESSAGE(*CLIENT->fd, ZMSG_KO);
        success = false;
    }
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_pie_index(server, i, CLIENT->tile->x, CLIENT->tile->y, success);
}
