#ifndef ZAPPY_SERVER_STOCK_H_
    #define ZAPPY_SERVER_STOCK_H_

    #include <stdbool.h>

    #define STOCK_ITEMS_AMOUNT 7

    // Items density
    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    #define SMALLEST_DENSITY(x) ((x < 1) ? 1 : x)

typedef struct {
    int food;
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

struct world_s;

void stock_initialize(stock_t *stock);
void stock_initialize_client(stock_t *stock);
void stock_initialize_world(struct world_s *world);
void stock_world_refill(struct world_s *world);
bool stock_exchange(stock_t *stock, stock_t *other, const char *element);
bool stock_verify_amount(stock_t *stock, const char *element, unsigned int amount);
void stock_associate_vars(stock_t *stock, stock_name_var_t vars[STOCK_ITEMS_AMOUNT]);
int stock_get_element_id(const char *element);

#endif
