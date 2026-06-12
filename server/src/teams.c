#include "teams.h"
#include "dynamic_arrays.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

team_data_t *team_data_init(const char *name, unsigned int max_clients)
{
    team_data_t *data = malloc(sizeof(team_data_t));

    if (data == NULL) {
        perror("malloc");
        exit(84);
    }
    data->name = name;
    data->clients = max_clients;
    data->tiles = malloc(sizeof(team_tiles_t));
    if (data->tiles == NULL)
        return NULL;
    DA_INIT(data->tiles, tile_t *);
    if (data->tiles->elems == NULL)
        return NULL;
    data->egg_tile_i = 0;
    return data;
}

void team_data_add_tile(team_data_t *team, tile_t *tile)
{
    DA_APPEND(team->tiles, tile);
}

tile_t *team_data_get_egg(team_data_t *team)
{
    if (team->egg_tile_i >= team->tiles->amount)
        return NULL;
    team->egg_tile_i++;
    return team->tiles->elems[team->egg_tile_i - 1];
}

void team_data_free(team_data_t *data)
{
    if (data->tiles) {
        free(data->tiles->elems);
        free(data->tiles);
    }
    free(data);
}

teams_t *teams_init(unsigned int max_clients)
{
    teams_t *teams = malloc(sizeof(teams_t));

    if (teams == NULL) {
        perror("malloc");
        exit(84);
    }
    DA_INIT(teams, team_data_t);
    teams->max_clients = max_clients;
    return teams;
}

void teams_append(teams_t *teams, const char *name)
{
    DA_APPEND(teams, team_data_init(name, teams->max_clients));
}

int teams_find_by_name(teams_t *teams, const char *name)
{
    for (size_t i = 0; i < teams->amount; i++) {
        if (strcmp(teams->elems[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void teams_free(teams_t *teams)
{
    DA_FREE(teams, team_data_free);
}
