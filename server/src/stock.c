#include "stock.h"
#include "world.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

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

static void world_restock(world_t *world, stock_t world_stock)
{
    long world_multiplier = world->height * world->width;
    size_t x, y;


    // Food
    for (size_t i = 0; i < SMALLEST_DENSITY(world_multiplier * FOOD_DENSITY) - world_stock.food; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[y][x].stock.food += 1;
    }

    // Linemate
    for (size_t i = 0; i < SMALLEST_DENSITY(world_multiplier * LINEMATE_DENSITY) - world_stock.linemate; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[y][x].stock.linemate += 1;
    }

    // Deraumere
    for (size_t i = 0; i < SMALLEST_DENSITY(world_multiplier * DERAUMERE_DENSITY) - world_stock.deraumere; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[y][x].stock.deraumere += 1;
    }

    // Sibur
    for (size_t i = 0; i < SMALLEST_DENSITY(world_multiplier * SIBUR_DENSITY) - world_stock.sibur; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[y][x].stock.sibur += 1;
    }

    // Mendiane
    for (size_t i = 0; i < SMALLEST_DENSITY(world_multiplier * MENDIANE_DENSITY) - world_stock.mendiane; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[y][x].stock.mendiane += 1;
    }

    // Phiras
    for (size_t i = 0; i < SMALLEST_DENSITY(world_multiplier * PHIRAS_DENSITY) - world_stock.phiras; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[y][x].stock.phiras += 1;
    }

    // Thystame
    for (size_t i = 0; i < SMALLEST_DENSITY(world_multiplier * THYSTAME_DENSITY) - world_stock.thystame; i++) {
        x = rand() % world->width;
        y = rand() % world->height;
        world->tiles[y][x].stock.thystame += 1;
    }
}

void stock_initialize_world(world_t *world)
{
    stock_t stock;

    stock_initialize(&stock);
    world_restock(world, stock);
}

void stock_world_refill(world_t *world)
{
    stock_t current_world_stock;

    // Get the current world stock
    stock_initialize(&current_world_stock);
    for (unsigned int y = 0; y < world->height; y++) {
        for (unsigned int x = 0; x < world->width; x++) {
            current_world_stock.food += world->tiles[y][x].stock.food;
            current_world_stock.linemate += world->tiles[y][x].stock.linemate;
            current_world_stock.deraumere += world->tiles[y][x].stock.deraumere;
            current_world_stock.sibur += world->tiles[y][x].stock.sibur;
            current_world_stock.mendiane += world->tiles[y][x].stock.mendiane;
            current_world_stock.phiras += world->tiles[y][x].stock.phiras;
            current_world_stock.thystame += world->tiles[y][x].stock.thystame;
        }
    }

    world_restock(world, current_world_stock);
}

void stock_associate_vars(stock_t *stock, stock_name_var_t vars[STOCK_ITEMS_AMOUNT])
{
    vars[0] = (stock_name_var_t){"food", &stock->food};
    vars[1] = (stock_name_var_t){"linemate", &stock->linemate};
    vars[2] = (stock_name_var_t){"deraumere", &stock->deraumere};
    vars[3] = (stock_name_var_t){"sibur", &stock->sibur};
    vars[4] = (stock_name_var_t){"mendiane", &stock->mendiane};
    vars[5] = (stock_name_var_t){"phiras", &stock->phiras};
    vars[6] = (stock_name_var_t){"thystame", &stock->thystame};
}

bool stock_verify_amount(stock_t *stock, const char *element, int amount)
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

int stock_get_element_id(const char *element)
{
    if (strcmp(element, "food") == 0)
        return 0;
    if (strcmp(element, "linemate") == 0)
        return 1;
    if (strcmp(element, "deraumere") == 0)
        return 2;
    if (strcmp(element, "sibur") == 0)
        return 3;
    if (strcmp(element, "mendiane") == 0)
        return 4;
    if (strcmp(element, "phiras") == 0)
        return 5;
    if (strcmp(element, "thystame") == 0)
        return 6;
    return -1;
}
