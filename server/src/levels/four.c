#include "level.h"

inline bool level_four_condition(server_t *server)
{
    return clients_get_amount_at_level_on_tile(server->clients, CLIENT->tile, 4) >= 4
        && CLIENT->tile->stock.linemate >= 1
        && CLIENT->tile->stock.deraumere >= 1
        && CLIENT->tile->stock.sibur >= 2
        && CLIENT->tile->stock.phiras >= 1;
}

void level_four_consume(stock_t *stock)
{
    stock->linemate--;
    stock->deraumere--;
    stock->sibur -= 2;
    stock->phiras--;
}
