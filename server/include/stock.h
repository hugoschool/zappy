#ifndef ZAPPY_SERVER_STOCK_H_
    #define ZAPPY_SERVER_STOCK_H_

    #include <stdbool.h>

    #define STOCK_ITEMS_AMOUNT 7

typedef struct {
    unsigned int food;
    unsigned int linemate;
    unsigned int deraumere;
    unsigned int sibur;
    unsigned int mendiane;
    unsigned int phiras;
    unsigned int thystame;
} stock_t;

typedef struct {
    const char *str;
    unsigned int *element;
} stock_name_var_t;

void stock_initialize_client(stock_t *stock);
void stock_initialize_world(stock_t *stock);
bool stock_exchange(stock_t *stock, stock_t *other, const char *element);

#endif
