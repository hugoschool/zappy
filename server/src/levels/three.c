#include "level.h"

inline bool level_three_condition(server_t *server)
{
    return clients_get_amount_at_level(server->clients, 3) == 2
        && CLIENT->tile->stock.linemate >= 2
        && CLIENT->tile->stock.sibur >= 1
        && CLIENT->tile->stock.phiras >= 2;
}

void level_three_consume(stock_t *stock)
{
    stock->linemate -= 2;
    stock->sibur--;
    stock->phiras -= 2;
}
