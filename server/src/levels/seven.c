#include "level.h"

inline bool level_seven_condition(server_t *server)
{
    return clients_get_amount_at_level_on_tile(server->clients, CLIENT->tile, 7) >= 6
        && CLIENT->tile->stock.linemate >= 2
        && CLIENT->tile->stock.deraumere >= 2
        && CLIENT->tile->stock.sibur >= 2
        && CLIENT->tile->stock.mendiane >= 2
        && CLIENT->tile->stock.phiras >= 2
        && CLIENT->tile->stock.thystame >= 1;
}

void level_seven_consume(stock_t *stock)
{
    stock->linemate -= 2;
    stock->deraumere -= 2;
    stock->sibur -= 2;
    stock->mendiane -= 2;
    stock->phiras -= 2;
    stock->thystame--;
}
