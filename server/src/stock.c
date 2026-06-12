#include "stock.h"
#include <stdbool.h>
#include <string.h>

static void stock_init(stock_t *stock)
{
    stock->food = 0;
    stock->linemate = 0;
    stock->deraumere = 0;
    stock->sibur = 0;
    stock->mendiane = 0;
    stock->phiras = 0;
    stock->thystame = 0;
}

void stock_initialize_client(stock_t *stock)
{
    stock_init(stock);
    stock->food = 10;
}

void stock_initialize_world(stock_t *stock)
{
    stock_init(stock);
    // TODO: all below is temporary, correctly initialize as the subject says
    stock->food = 3;
    stock->linemate = 10;
}

static void stock_associate_vars(stock_t *stock, stock_name_var_t vars[STOCK_ITEMS_AMOUNT])
{
    vars[0] = (stock_name_var_t){"food", &stock->food};
    vars[1] = (stock_name_var_t){"linemate", &stock->linemate};
    vars[2] = (stock_name_var_t){"deraumere", &stock->deraumere};
    vars[3] = (stock_name_var_t){"sibur", &stock->sibur};
    vars[4] = (stock_name_var_t){"mendiane", &stock->mendiane};
    vars[5] = (stock_name_var_t){"phiras", &stock->phiras};
    vars[6] = (stock_name_var_t){"thystame", &stock->thystame};
}

bool stock_verify_amount(stock_t *stock, const char *element, unsigned int amount)
{
    stock_name_var_t stock_vars[STOCK_ITEMS_AMOUNT];

    stock_associate_vars(stock, stock_vars);
    for (size_t i = 0; i < STOCK_ITEMS_AMOUNT; i++) {
        if (strcmp(stock_vars[i].str, element) == 0)
            return (*stock_vars[i].element) == amount;
    }
    return false;
}

// Returns true if possible
// Returns false if impossible
bool stock_exchange(stock_t *stock, stock_t *other, const char *element)
{
    stock_name_var_t stock_vars[STOCK_ITEMS_AMOUNT];
    stock_name_var_t other_vars[STOCK_ITEMS_AMOUNT];

    stock_associate_vars(stock, stock_vars);
    stock_associate_vars(other, other_vars);
    for (size_t i = 0; i < STOCK_ITEMS_AMOUNT; i++) {
        if (strcmp(stock_vars[i].str, element) == 0) {
            if (*stock_vars[i].element > 0) {
                (*stock_vars[i].element)--;
                (*other_vars[i].element)++;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
