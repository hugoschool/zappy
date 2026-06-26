#ifndef ZAPPY_SERVER_FREQUENCY_H_
    #define ZAPPY_SERVER_FREQUENCY_H_

    #include "server.h"

    #define FOOD_CONSUMING_FREQ 126
    #define WORLD_RESTOCKING_FREQ 20

double calculate_time_elapsed(struct timespec start);
void frequency_handling(server_t *server);
void calculate_timeout(server_t *server);

#endif
