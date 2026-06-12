#ifndef ZAPPY_SERVER_TEAMS_H_
    #define ZAPPY_SERVER_TEAMS_H_

    #include "world.h"
    #include <stddef.h>

    #define TEAM_I(i) server->teams->elems[i]
    #define TEAM_GRAPHIC_NAME "GRAPHIC"

typedef struct {
    tile_t **elems;
    size_t amount;
    size_t size;
} team_tiles_t;

typedef struct {
    // Name of the team
    const char *name;

    // Amount of clients left that can connect to this team
    unsigned int clients;

    // Location of eggs on the world tiles
    team_tiles_t *tiles;

    // Egg tile index
    unsigned int egg_tile_i;
} team_data_t;

team_data_t *team_data_init(const char *name, unsigned int max_clients);
void team_data_add_tile(team_data_t *team, tile_t *tile);
tile_t *team_data_get_egg(team_data_t *team);
void team_data_free(team_data_t *data);

typedef struct {
    team_data_t **elems;
    size_t amount;
    size_t size;

    // Max amount of clients given in args
    unsigned int max_clients;
} teams_t;

teams_t *teams_init(unsigned int max_clients);
void teams_append(teams_t *teams, const char *name);
int teams_find_by_name(teams_t *teams, const char *name);
void teams_free(teams_t *teams);

#endif
