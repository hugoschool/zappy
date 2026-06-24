#include "commands.h"
#include "messages.h"
#include "server.h"
#include <stddef.h>
#include <stdio.h>

void command_graphic_pic_index(server_t *server, int graphic_i, int x, int y, int level, int *player_array, size_t player_array_amount)
{
    char buffer[CMDS_TEMP_BUFFER_SIZE] = {0};
    char number_buffer[CMDS_TEMP_BUFFER_SIZE] = {0};

    for (size_t i = 0; i < player_array_amount; i++) {
        snprintf(number_buffer, CMDS_TEMP_BUFFER_SIZE, "#%d", PLAYER_I(player_array[i])->player_graphical_index);
        strcat(buffer, number_buffer);
        if (i == player_array_amount - 1)
            strcat(buffer, " ");
    }
    dprintf(*CLIENT_I(graphic_i)->fd, "pic %d %d %d %s" ZMSG_END_SEQ, x, y, level, buffer);
}
