#include "clients.h"
#include "commands.h"
#include "server.h"
#include <stdio.h>
#include <time.h>

// Returns the time elapsed in seconds
static double time_since_start(struct timespec start)
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);

    return (double)(now.tv_sec - start.tv_sec) + (double)(now.tv_nsec - start.tv_nsec) / 1000000000.0;
}

static void verify_frequency(server_t *server, size_t i)
{
    server->index = i;
    double time_elapsed = time_since_start(CLIENT->command_start);

    // TODO remove, this is for future debug (no command are implemented so it cannot be tested)
    printf("fd: %d, command current duration: %lf (in seconds)\n", *CLIENT->fd, time_elapsed);
    if (time_elapsed >= (double)CLIENT->command->time_limit / (double)server->freq) {
        CLIENT->command->function(server);
        CLIENT->is_command_running = false;
        CLIENT->command = NULL;
    }
}

void frequency_handling(server_t *server)
{
    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
        if (server->clients->elems[i]->is_command_running == true) {
            verify_frequency(server, i);
        }
    }
}

void calculate_timeout(server_t *server)
{
    bool has_timeout = false;

    for (size_t i = CLIENT_INITIAL_INDEX; i < server->clients->amount; i++) {
        if (server->clients->elems[i]->is_command_running == true) {
            double time_elapsed = time_since_start(server->clients->elems[i]->command_start);
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
