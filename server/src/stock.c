#include "stock.h"
#include "world.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void stock_initialize(stock_t *stock)
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
    stock_initialize(stock);
    stock->food = 10;
}

void stock_initialize_world(world_t *world)
{    
    size_t world_multiplier = world->height * world->width;
    size_t x, y;
    
    srand(time(NULL));

    // Food
    for (size_t i = 0; i < world_multiplier * FOOD_DENSITY; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[ZW_POS(world->width, x, y)].stock.food += 1;
    }

    // Linemate
    for (size_t i = 0; i < world_multiplier * LINEMATE_DENSITY; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[ZW_POS(world->width, x, y)].stock.linemate += 1;
    }

    // Deraumere
    for (size_t i = 0; i < world_multiplier * DERAUMERE_DENSITY; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[ZW_POS(world->width, x, y)].stock.deraumere += 1;
    }

    // Sibur
    for (size_t i = 0; i < world_multiplier * SIBUR_DENSITY; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[ZW_POS(world->width, x, y)].stock.sibur += 1;
    }

    // Mendiane
    for (size_t i = 0; i < world_multiplier * MENDIANE_DENSITY; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[ZW_POS(world->width, x, y)].stock.mendiane += 1;
    }

    // Phiras
    for (size_t i = 0; i < world_multiplier * PHIRAS_DENSITY; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[ZW_POS(world->width, x, y)].stock.phiras += 1;
    }

    // Thystame
    for (size_t i = 0; i < world_multiplier * THYSTAME_DENSITY; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[ZW_POS(world->width, x, y)].stock.thystame += 1;
    }
}

// TODO create a the function that restock the world (called by frequency)

void stock_associate_vars(stock_t *stock, stock_name_var_t vars[STOCK_ITEMS_AMOUNT])
{
    vars[0] = (stock_name_var_t){"food", (unsigned int *)&stock->food};
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
