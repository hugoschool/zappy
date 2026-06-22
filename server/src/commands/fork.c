#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"
#include "teams.h"
#include "world.h"

void command_fork(server_t *server)
{
    CLIENT->team->clients++;
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_pfk_index(server, i, CLIENT->player_nb);
    eggs_add_world_and_tile(server->world, CLIENT->tile);
    team_data_add_tile(CLIENT->team, CLIENT->tile);
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++)
        if (CLIENT_I(i)->is_graphical == true)
            command_graphic_enw_index(
                server, i,
                CLIENT->player_nb,
                ZW_LAST_EGG(server->world->eggs),
                CLIENT->tile->x, CLIENT->tile->y
            );
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
