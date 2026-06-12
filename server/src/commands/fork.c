#include "messages.h"
#include "server.h"
#include "teams.h"
#include "world.h"

void command_fork(server_t *server)
{
    tile_t *egg = NULL;

    CLIENT->team->clients++;
    egg = world_generate_egg(server->world);
    team_data_add_tile(CLIENT->team, egg);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
