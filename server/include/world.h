#ifndef ZAPPY_SERVER_WORLD_H_
    #define ZAPPY_SERVER_WORLD_H_

    #include "stock.h"
    #include <stdbool.h>

    #define ZW_POS(width, x, y) width * y + x

typedef struct {
    // Has an egg
    // TODO: must be modified for forks
    bool egg;
    // Stock of the tile
    stock_t stock;
    // Coordinates
    unsigned int x;
    unsigned int y;
} tile_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    tile_t *tiles;
} world_t;

world_t *world_init(unsigned int width, unsigned int height);
tile_t *world_generate_egg(world_t *world);
void world_free(world_t *world);

#endif
