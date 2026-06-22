#include "level.h"

inline bool level_one_condition(server_t *server)
{
    // No need to check for nb_players as we're sure there's already one.
    return CLIENT->tile->stock.linemate >= 1;
}

void level_one_consume(stock_t *stock)
{
    stock->linemate--;
}
