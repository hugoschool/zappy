#include "frequency.h"
#include "clients.h"
#include "commands.h"
#include "server.h"
#include "world.h"
#include <stdio.h>
#include <time.h>

// Returns the time elapsed in seconds
static double calculate_time_elapsed(struct timespec start)
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);

    return (double)(now.tv_sec - start.tv_sec) + (double)(now.tv_nsec - start.tv_nsec) / 1000000000.0;
}

static void verify_frequency(server_t *server)
{
    double time_elapsed = calculate_time_elapsed(CLIENT->command_start);

    // TODO remove, this is for future debug (no command are implemented so it cannot be tested)
    printf("fd: %d, command current duration: %lf (in seconds)\n", *CLIENT->fd, time_elapsed);
    if (time_elapsed >= (double)CLIENT->command->time_limit / (double)server->freq) {
        CLIENT->command->function(server);
        CLIENT->is_command_running = false;
        CLIENT->command = NULL;
    }
}

static void consume_food(server_t *server)
{
    double time_elapsed = calculate_time_elapsed(CLIENT->food_clock);
    
    // TODO remove this debug printf
    printf("food: %d, eating duration: %lf (in seconds) -> %lf + %lf\n", CLIENT->stock.food, time_elapsed + CLIENT->food_freq_offset, time_elapsed, CLIENT->food_freq_offset);
    if (time_elapsed + CLIENT->food_freq_offset >= (FOOD_CONSUMING_FREQ / (double)server->freq)) {
        int food_consumed = (int)((time_elapsed + CLIENT->food_freq_offset) / ((FOOD_CONSUMING_FREQ / (double)server->freq)));

        CLIENT->stock.food -= food_consumed;
        printf("%d: food\n", CLIENT->stock.food);
        if (CLIENT->stock.food < 0) {
            // TODO kill the client (starving)
        }
        CLIENT->food_freq_offset = (time_elapsed + CLIENT->food_freq_offset) - (food_consumed * ((FOOD_CONSUMING_FREQ / (double)server->freq)));
        timespec_get(&CLIENT->food_clock, TIME_UTC);
    }
}

static void world_frequency_handling(server_t *server)
{
    double time_elapsed = calculate_time_elapsed(server->world->clock);

    if (time_elapsed + server->world->restock_offset >= (WORLD_RESTOCKING_FREQ / (double)server->freq)) {
        int nb_restocks = (int)((time_elapsed + server->world->restock_offset) / ((WORLD_RESTOCKING_FREQ / (double)server->freq)));

        world_refill(server->world);
        server->world->restock_offset = (time_elapsed + server->world->restock_offset) - (nb_restocks * ((WORLD_RESTOCKING_FREQ / (double)server->freq)));
        timespec_get(&server->world->clock, TIME_UTC);
    }
}

void frequency_handling(server_t *server)
{
    world_frequency_handling(server);

    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
        server->index = i;
        if (CLIENT->stock.food != -1) {
            consume_food(server);
        }
        if (CLIENT->is_command_running == true) {
            verify_frequency(server);
        }
    }
}

void calculate_timeout(server_t *server)
{
    bool has_timeout = false;

    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
        if (server->clients->elems[i]->is_command_running == true) {
            double time_elapsed = calculate_time_elapsed(server->clients->elems[i]->command_start);
            double time_until_end = ((double)server->clients->elems[i]->command->time_limit / (double)server->freq) - time_elapsed;

            // Remove a quarter of the poll timeout to make sure it works
            int poll_timeout = (int)(time_until_end * 1000);
            poll_timeout = poll_timeout - poll_timeout / 4;

            if (poll_timeout < DEFAULT_POLL_TIMEOUT) {
                has_timeout = false;
                break;
            } else if (has_timeout == false) {
                server->poll_timeout = poll_timeout;
                has_timeout = true;
            } else if (poll_timeout < server->poll_timeout) {
                server->poll_timeout = poll_timeout;
            }
        }
    }
    if (has_timeout == false) {
        server->poll_timeout = DEFAULT_POLL_TIMEOUT;
    }
}

// TODO

/* ¡¡Restocking!!
The server spawns resources upon starting and every 20 time units.
It follows this set of rules:
    - on Trantor you must find at least one of each ressource and food on the floor.
    - resources should be evenly spread across the map.
    - the ressource quantity can be found with the following formula: map_width * map_height * density
Resource density:
    food        0.5
    linemate    0.3
    deraumere   0.15
    sibur       0.1
    mendiane    0.1
    phiras      0.08
    thystame    0.05
for instance on a 10 by 10 world there is 50 food and 5 thystame.
*/

// TODO create a function based on a server clock that called the restock function for the world
