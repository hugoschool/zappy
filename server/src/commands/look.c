#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"
#include "stock.h"
#include "world.h"
#include <stdio.h>

struct look_coordinates_s {
    int xStart;
    int xEnd;

    int yStart;
    int yEnd;
};

// One iteration of moving coordinates
static void move_coordinates(struct look_coordinates_s *coordinates, client_direction_t direction)
{
    switch (direction) {
        case RIGHT:
            coordinates->xStart += 1;
            coordinates->xEnd = coordinates->xStart;
            coordinates->yStart -= 1;
            coordinates->yEnd += 1;
            break;
        case UP:
            coordinates->xStart -= 1;
            coordinates->xEnd += 1;
            coordinates->yStart += 1;
            coordinates->yEnd = coordinates->yStart;
            break;
        case LEFT:
            coordinates->xStart -= 1;
            coordinates->xEnd = coordinates->xStart;
            coordinates->yStart -= 1;
            coordinates->yEnd += 1;
            break;
        case DOWN:
            coordinates->xStart -= 1;
            coordinates->xEnd += 1;
            coordinates->yStart -= 1;
            coordinates->yEnd = coordinates->yStart;
            break;
    }
}

// Returns true if there is another element in this stock superior to 0
// Useful to add the space in between elements
// Not my proudest function name
static bool is_there_a_next_stock_amount(stock_name_var_t *stock_vars, int current_i)
{
    for (size_t i = current_i + 1; i < STOCK_ITEMS_AMOUNT; i++) {
        if (*stock_vars[i].element > 0)
            return true;
    }
    return false;
}

static bool is_player_on_tile(server_t *server, tile_t *tile)
{
    for (size_t i = 0; i < server->clients->amount; i++) {
        if (CLIENT_I(i)->tile == tile)
            return true;
    }
    return false;
}

static void buffer_add_tile_stock(server_t *server, char buffer[CMDS_TEMP_BUFFER_SIZE], tile_t *tile, unsigned int *amount)
{
    char temp_buffer[CMDS_TEMP_BUFFER_SIZE] = {0};
    stock_name_var_t stock_vars[STOCK_ITEMS_AMOUNT];

    stock_associate_vars(&tile->stock, stock_vars);
    if (is_player_on_tile(server, tile))
        strcat(buffer, "player");
    if (is_there_a_next_stock_amount(stock_vars, -1))
        strcat(buffer, " ");
    for (size_t i = 0; i < STOCK_ITEMS_AMOUNT; i++) {
        memset(temp_buffer, 0, CMDS_TEMP_BUFFER_SIZE);
        for (unsigned int amount = 0; amount < *stock_vars[i].element; amount++) {
            strncat(temp_buffer, stock_vars[i].str, strlen(stock_vars[i].str));
            if (amount != *stock_vars[i].element - 1)
                strcat(temp_buffer, " ");
        }
        if (is_there_a_next_stock_amount(stock_vars, i))
            strcat(temp_buffer, " ");
        strncat(buffer, temp_buffer, strlen(temp_buffer));
    }
    if (*amount > 0) {
        strcat(buffer, ",");
        (*amount)--;
    }
}

static unsigned int get_amount_of_tiles(server_t *server)
{
    unsigned int amount = 0;
    struct look_coordinates_s coordinates = {
        .xStart = CLIENT->tile->x,
        .xEnd = CLIENT->tile->x,
        .yStart = CLIENT->tile->y,
        .yEnd = CLIENT->tile->y,
    };

    for (unsigned int level = 1; level <= CLIENT->level; level++) {
        move_coordinates(&coordinates, CLIENT->direction);
        for (int y = coordinates.yStart; y <= coordinates.yEnd; y++) {
            for (int x = coordinates.xStart; x <= coordinates.xEnd; x++) {
                amount++;
            }
        }
    }
    return amount;
}

// TODO: verify buffer concatenation
void command_look(server_t *server)
{
    char buffer[CMDS_TEMP_BIG_BUFFER_SIZE] = {0};
    struct look_coordinates_s coordinates = {
        .xStart = CLIENT->tile->x,
        .xEnd = CLIENT->tile->x,
        .yStart = CLIENT->tile->y,
        .yEnd = CLIENT->tile->y,
    };
    tile_t *tile = NULL;
    unsigned int amount = get_amount_of_tiles(server);

    strcat(buffer, "[");
    buffer_add_tile_stock(server, buffer, CLIENT->tile, &amount);
    for (unsigned int level = 1; level <= CLIENT->level; level++) {
        move_coordinates(&coordinates, CLIENT->direction);
        for (int y = coordinates.yStart; y <= coordinates.yEnd; y++) {
            for (int x = coordinates.xStart; x <= coordinates.xEnd; x++) {
                tile = &server->world->tiles[ZW_POS_MOD(server->world->width, server->world->height, x, y)];
                buffer_add_tile_stock(server, buffer, tile, &amount);
            }
        }
    }
    strcat(buffer, "]");
    dprintf(*CLIENT->fd, "%s" ZMSG_END_SEQ, buffer);
}
