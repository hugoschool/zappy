#include "level.h"

inline bool level_two_condition(server_t *server)
{
    return clients_get_amount_at_level(server->clients, 2) == 2
        && CLIENT->tile->stock.linemate >= 1
        && CLIENT->tile->stock.deraumere >= 1
        && CLIENT->tile->stock.sibur >= 1;
}

void level_two_consume(stock_t *stock)
{
    stock->linemate--;
    stock->deraumere--;
    stock->sibur--;
}
