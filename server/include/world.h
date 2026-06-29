#ifndef ZAPPY_SERVER_WORLD_H_
    #define ZAPPY_SERVER_WORLD_H_

    #include "stock.h"
    #include <stdbool.h>
    #include <stddef.h>
    #include <time.h>

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

    // 2D Array containing the tiles
    // Ex: tiles[y][x]
    tile_t **tiles;

    // Offset for world restocking
    double restock_offset;

    // Food clock
    struct timespec clock;

    // All the eggs of the world
    eggs_t *eggs;
} world_t;

struct server_s;

world_t *world_init(struct server_s *server, unsigned int width, unsigned int height);
tile_t *world_generate_egg(world_t *world);
tile_t *world_get_wrapped_tile(world_t *world, int x, int y);
void world_free(world_t *world);

#endif
