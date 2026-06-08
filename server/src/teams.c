#include "teams.h"
#include "dynamic_arrays.h"
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
    return data;
}

void team_data_free(team_data_t *data)
{
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
