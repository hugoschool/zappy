#include "level.h"

inline bool level_five_condition(server_t *server)
{
    return clients_get_amount_at_level(server->clients, 5) == 4
        && CLIENT->tile->stock.linemate >= 1
        && CLIENT->tile->stock.deraumere >= 2
        && CLIENT->tile->stock.sibur >= 1
        && CLIENT->tile->stock.mendiane >= 3;
}

void level_five_consume(stock_t *stock)
{
    stock->linemate--;
    stock->deraumere -= 2;
    stock->sibur--;
    stock->mendiane -= 3;
}
