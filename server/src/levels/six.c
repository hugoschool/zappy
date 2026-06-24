#include "level.h"

inline bool level_six_condition(server_t *server)
{
    return clients_get_amount_at_level_on_tile(server->clients, CLIENT->tile, 6) >= 6
        && CLIENT->tile->stock.linemate >= 1
        && CLIENT->tile->stock.deraumere >= 2
        && CLIENT->tile->stock.sibur >= 3
        && CLIENT->tile->stock.phiras >= 1;
}

void level_six_consume(stock_t *stock)
{
    stock->linemate--;
    stock->deraumere -= 2;
    stock->sibur -= 3;
    stock->phiras--;
}
