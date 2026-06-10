#include "clients.h"
#include "commands.h"
#include "server.h"
#include <stdio.h>
#include <time.h>

static void verify_frequency(server_t *server, client_data_t *data)
{
    clock_t current_clock = clock();
    clock_t time_elapsed = current_clock - data->command_start;

    // TODO remove, this is for future debug (no command are implemented so it cannot be tested)
    printf("fd: %d, command current duration: %ld\n", *data->fd, time_elapsed);
    if (time_elapsed >= (double)data->command->time_limit / (double)server->freq) {
        data->is_command_running = false;
        data->command->function(server);
        // TODO maybe change this
        data->command = NULL;
    }
}

void frequency_handling(server_t *server)
{
    for (size_t i = 0; i < server->clients->amount; i++) {
        if (server->clients->elems[i]->is_command_running == true) {
            verify_frequency(server, server->clients->elems[i]);
        }
    }
}
