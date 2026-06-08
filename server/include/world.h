#ifndef ZAPPY_SERVER_WORLD_H_
    #define ZAPPY_SERVER_WORLD_H_

typedef struct {
    unsigned int x;
    unsigned int y;
} world_t;

world_t *world_init(unsigned int x, unsigned int y);
void world_free(world_t *world);

#endif
