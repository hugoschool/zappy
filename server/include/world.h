#ifndef ZAPPY_SERVER_WORLD_H_
    #define ZAPPY_SERVER_WORLD_H_

    #include "stock.h"
    #include <stdbool.h>
    #include <stddef.h>
    #include <time.h>

    #define ZW_POS(width, x, y) width * y + x
    #define ZW_POS_MOD(width, height, x, y) (width * (y % height)) + (x % width)

    #define ZW_LAST_EGG(eggs) eggs->elems[eggs->amount - 1]

typedef struct {
    int *elems;
    size_t amount;
    size_t size;

    // Only used when creating eggs
    size_t egg_nb;
} eggs_t;

struct tile_s;
struct world_s;

eggs_t *eggs_init(void);
void eggs_add(eggs_t *eggs);
void eggs_add_content(eggs_t *eggs, int i);
void eggs_add_world_and_tile(struct world_s *world, struct tile_s *tile);
int eggs_consume_one(eggs_t *eggs);

typedef struct tile_s {
    // The INDICES of the eggs in the world structure
    eggs_t *eggs;
    // Stock of the tile
    stock_t stock;
    // Coordinates
    unsigned int x;
    unsigned int y;
} tile_t;

void tile_destroy_eggs(tile_t *tile, struct world_s *world);

typedef struct world_s {
    // Size of the entire world
    unsigned int width;
    unsigned int height;

    // All of the tiles
    tile_t *tiles;

    // Offset for world restocking
    double restock_offset;

    // Food clock
    struct timespec clock;

    // All the eggs of the world
    eggs_t *eggs;
} world_t;

world_t *world_init(unsigned int width, unsigned int height);
tile_t *world_generate_egg(world_t *world);
void world_free(world_t *world);

#endif
