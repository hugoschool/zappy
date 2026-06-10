#include "world.h"
#include <stdlib.h>

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
    // TODO: generate stock
    return world;
}

tile_t *world_generate_egg(world_t *world)
{
    tile_t *tile = NULL;
    int x = rand() % world->width;
    int y = rand() % world->height;

    while (world->tiles[x * (y + 1)].egg == true) {
        x = rand() % world->width;
        y = rand() % world->height;
    }
    tile = &world->tiles[x * (y + 1)];
    tile->egg = true;
    return tile;
}

void world_free(world_t *world)
{
    if (world->tiles)
        free(world->tiles);
    free(world);
}
