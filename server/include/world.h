#ifndef ZAPPY_SERVER_WORLD_H_
    #define ZAPPY_SERVER_WORLD_H_

    #include "stock.h"
    #include <stdbool.h>
    #include <time.h>

    #define ZW_POS(width, x, y) width * y + x
    #define ZW_POS_MOD(width, height, x, y) (width * (y % height)) + (x % width)

typedef struct {
    // The amount of eggs on this tile
    int egg;
    // Stock of the tile
    stock_t stock;
    // Coordinates
    unsigned int x;
    unsigned int y;
} tile_t;

typedef struct world_s {
    unsigned int width;
    unsigned int height;
    tile_t *tiles;
    // Offset for world restocking
    double restock_offset;
    // Food clock
    struct timespec clock;
} world_t;

world_t *world_init(unsigned int width, unsigned int height);
tile_t *world_generate_egg(world_t *world);
void world_free(world_t *world);

#endif
