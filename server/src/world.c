#include "world.h"
#include <stdlib.h>

world_t *world_init(unsigned int x, unsigned int y)
{
    world_t *world = calloc(1, sizeof(world_t));

    if (world == NULL)
        return NULL;
    world->x = x;
    world->y = y;
    return world;
}

void world_free(world_t *world)
{
    free(world);
}
