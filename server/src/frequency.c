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

static void verify_frequency(server_t *server, int i)
{
    double time_elapsed = calculate_time_elapsed(PLAYER_I(i)->command_start);

    // TODO remove, this is for future debug (no command are implemented so it cannot be tested)
    printf("fd: %d, command current duration: %lf (in seconds)\n", *PLAYER_I(i)->fd, time_elapsed);
    if (time_elapsed >= (double)PLAYER_I(i)->command->time_limit / (double)server->freq) {
        unsigned int prev_index = server->index;
        int index = clients_find_by_player_nb(server->clients, i);

        if (index == -1)
            return;
        server->index = index;
        PLAYER_I(i)->command->function(server);
        PLAYER_I(i)->is_command_running = false;
        PLAYER_I(i)->command = NULL;
        server->index = prev_index;
    }
}

static void consume_food(server_t *server, int i)
{
    double time_elapsed = calculate_time_elapsed(PLAYER_I(i)->food_clock);

    // TODO remove this debug printf
    printf("food: %d, eating duration: %lf (in seconds) -> %lf + %lf\n", PLAYER_I(i)->stock.food, time_elapsed + PLAYER_I(i)->food_freq_offset, time_elapsed, PLAYER_I(i)->food_freq_offset);
    if (time_elapsed + PLAYER_I(i)->food_freq_offset >= (FOOD_CONSUMING_FREQ / (double)server->freq)) {
        int food_consumed = (int)((time_elapsed + PLAYER_I(i)->food_freq_offset) / ((FOOD_CONSUMING_FREQ / (double)server->freq)));

        PLAYER_I(i)->stock.food -= food_consumed;
        printf("%d: food\n", PLAYER_I(i)->stock.food);
        if (PLAYER_I(i)->stock.food < 0) {
            // TODO kill the client (starving)
        }
        PLAYER_I(i)->food_freq_offset = (time_elapsed + PLAYER_I(i)->food_freq_offset) - (food_consumed * ((FOOD_CONSUMING_FREQ / (double)server->freq)));
        timespec_get(&PLAYER_I(i)->food_clock, TIME_UTC);
    }
}

static void world_frequency_handling(server_t *server)
{
    double time_elapsed = calculate_time_elapsed(server->world->clock);

    if (time_elapsed + server->world->restock_offset >= (WORLD_RESTOCKING_FREQ / (double)server->freq)) {
        int nb_restocks = (int)((time_elapsed + server->world->restock_offset) / ((WORLD_RESTOCKING_FREQ / (double)server->freq)));

        stock_world_refill(server->world);
        server->world->restock_offset = (time_elapsed + server->world->restock_offset) - (nb_restocks * ((WORLD_RESTOCKING_FREQ / (double)server->freq)));
        timespec_get(&server->world->clock, TIME_UTC);
    }
}

void frequency_handling(server_t *server)
{
    world_frequency_handling(server);

    for (size_t i = 0; i < server->players->amount; i++) {
        if (PLAYER_I(i)->stock.food != -1) {
            consume_food(server, i);
        }
        if (PLAYER_I(i)->is_command_running == true) {
            verify_frequency(server, i);
        }
    }
}

void calculate_timeout(server_t *server)
{
    bool has_timeout = false;

    for (size_t i = 0; i < server->players->amount; i++) {
        if (PLAYER_I(i)->is_command_running == true) {
            double time_elapsed = calculate_time_elapsed(PLAYER_I(i)->command_start);
            double time_until_end = ((double)PLAYER_I(i)->command->time_limit / (double)server->freq) - time_elapsed;

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
