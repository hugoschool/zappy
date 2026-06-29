#include "dynamic_arrays.h"
#include "world.h"
#include "stock.h"
#include <stdlib.h>

eggs_t *eggs_init(void)
{
    eggs_t *eggs = malloc(sizeof(eggs_t));

    if (eggs == NULL)
        return NULL;
    DA_INIT(eggs, int);
    if (eggs->elems == NULL)
        return NULL;
    eggs->egg_nb = 0;
    return eggs;
}

void eggs_add(eggs_t *eggs)
{
    DA_APPEND(eggs, eggs->egg_nb);
    eggs->egg_nb++;
}

void eggs_add_content(eggs_t *eggs, int i)
{
    DA_APPEND(eggs, i);
}

void eggs_add_world_and_tile(world_t *world, tile_t *tile)
{
    eggs_add(world->eggs);
    eggs_add_content(tile->eggs, world->eggs->elems[world->eggs->amount - 1]);
}

// Returns the id of the egg that was consumed
int eggs_consume_one(eggs_t *eggs)
{
    int id = -1;

    if (eggs->amount <= 0)
        return -1;
    id = eggs->elems[eggs->amount - 1];
    eggs->amount--;
    return id;
}

void eggs_remove_content(eggs_t *eggs, int content)
{
    for (size_t i = 0; i < eggs->amount; i++) {
        if (eggs->elems[i] != content)
            continue;
        eggs->elems[i] = eggs->elems[eggs->amount - 1];
        eggs->amount--;
    }
}

void eggs_free(eggs_t *eggs)
{
    if (eggs == NULL)
        return;
    free(eggs->elems);
    free(eggs);
}

static void tile_init(tile_t *tile, unsigned int x, unsigned int y)
{
    tile->eggs = eggs_init();
    if (tile->eggs == NULL) {
        perror("eggs_init");
        exit(84);
    }
    tile->x = x;
    tile->y = y;
    stock_initialize(&tile->stock);
}

void tile_destroy_eggs(tile_t *tile, world_t *world)
{
    for (size_t i = 0; i < tile->eggs->amount; i++) {
        eggs_remove_content(world->eggs, tile->eggs->elems[i]);
    }
    tile->eggs->amount = 0;
}

static void world_initialize_tiles(world_t *world)
{
    for (unsigned int y = 0; y < world->height; y++) {
        for (unsigned int x = 0; x < world->width; x++) {
            tile_init(&world->tiles[y][x], x, y);
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
    world->restock_offset = 0;
    timespec_get(&world->clock, TIME_UTC);
    world->tiles = calloc(height, sizeof(tile_t *));
    if (world->tiles == NULL)
        return NULL;
    for (unsigned int y = 0; y < world->height; y++) {
        world->tiles[y] = calloc(width, sizeof(tile_t));
        if (world->tiles[y] == NULL)
            return NULL;
    }
    world->eggs = eggs_init();
    if (world->eggs == NULL)
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

    while (world->tiles[y][x].eggs->amount > 0) {
        x = rand() % world->width;
        y = rand() % world->height;
    }
    tile = &world->tiles[y][x];
    eggs_add_world_and_tile(world, tile);
    return tile;
}

static void world_free_tiles(world_t *world)
{
    for (unsigned int y = 0; y < world->height; y++) {
        for (unsigned int x = 0; x < world->width; x++) {
            eggs_free(world->tiles[y][x].eggs);
        }
        free(world->tiles[y]);
    }
    free(world->tiles);
}

tile_t *world_get_wrapped_tile(world_t *world, int x, int y)
{
    int new_x = x;
    int new_y = y;

    if (new_x < 0) {
        new_x = (new_x * -1) % (int)world->width;
        new_x = (int)world->width - new_x;
    }
    if (new_x >= (int)world->width)
        new_x %= world->width;
    if (new_y < 0) {
        new_y = (new_y * -1) % (int)world->height;
        new_y = (int)world->height - new_y;
    }
    if (new_y >= (int)world->height)
        new_y %= world->height;
    return &world->tiles[new_y][new_x];
}

void world_free(world_t *world)
{
    if (world->tiles)
        world_free_tiles(world);
    if (world->eggs)
        eggs_free(world->eggs);
    free(world);
}
