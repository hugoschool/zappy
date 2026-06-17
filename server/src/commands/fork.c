#include "messages.h"
#include "server.h"
#include "teams.h"
#include "world.h"

void command_fork(server_t *server)
{
    CLIENT->team->clients++;
    eggs_add_world_and_tile(server->world, CLIENT->tile);
    team_data_add_tile(CLIENT->team, CLIENT->tile);
    WRITE_MESSAGE(*CLIENT->fd, ZMSG_OK);
}
