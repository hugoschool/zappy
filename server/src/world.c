#include "world.h"
#include "stock.h"
#include <stdlib.h>

static void tile_init(tile_t *tile, unsigned int x, unsigned int y)
{
    tile->egg = 0;
    tile->x = x;
    tile->y = y;
    stock_initialize(&tile->stock);
}

static void world_initialize_tiles(world_t *world)
{
    for (unsigned int y = 0; y < world->height; y++) {
        for (unsigned int x = 0; x < world->width; x++) {
            tile_init(&world->tiles[ZW_POS(world->width, x, y)], x, y);
        }
    }
}

world_t *world_init(unsigned int width, unsigned int height)
{
    world_t *world = calloc(1, sizeof(world_t));

    if (world == NULL)
        return NULL;
    world->width = width;
    world->height = height;
    world->tiles = calloc(width * height, sizeof(tile_t));
    if (world->tiles == NULL)
        return NULL;
    world_initialize_tiles(world);
    stock_initialize_world(world);
    return world;
}

tile_t *world_generate_egg(world_t *world)
{
    tile_t *tile = NULL;
    int x = rand() % world->width;
    int y = rand() % world->height;

    while (world->tiles[ZW_POS(world->width, x, y)].egg > 0) {
        x = rand() % world->width;
        y = rand() % world->height;
    }
    tile = &world->tiles[ZW_POS(world->width, x, y)];
    tile->egg++;
    return tile;
}

void world_free(world_t *world)
{
    if (world->tiles)
        free(world->tiles);
    free(world);
}
