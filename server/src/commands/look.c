#include "clients.h"
#include "commands.h"
#include "messages.h"
#include "server.h"
#include "stock.h"
#include "utils.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>

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
            coordinates->yStart -= 1;
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
            coordinates->yStart += 1;
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

static int players_amount_on_tile(server_t *server, tile_t *tile)
{
    int player_amount = 0;

    for (size_t i = 0; i < server->players->amount; i++) {
        if (PLAYER_I(i)->tile == tile)
            player_amount++;
    }
    return player_amount;
}

static void buffer_add_tile_stock(server_t *server, string_vec_t *vec, tile_t *tile, unsigned int *amount)
{
    stock_name_var_t stock_vars[STOCK_ITEMS_AMOUNT];
    int player_amount = players_amount_on_tile(server, tile);

    stock_associate_vars(&tile->stock, stock_vars);
    for (int i = 0; i < player_amount; i++) {
        string_vec_append(vec, " player");
    }
    if (is_there_a_next_stock_amount(stock_vars, -1))
        string_vec_append(vec, " ");
    for (size_t i = 0; i < STOCK_ITEMS_AMOUNT; i++) {
        for (int elem_amount = 0; elem_amount < *(stock_vars[i].element); elem_amount++) {
            string_vec_append(vec, (char *)stock_vars[i].str);
            if (elem_amount != *(stock_vars[i].element) - 1)
                string_vec_append(vec, " ");
        }
        if (*(stock_vars[i].element) > 0 && is_there_a_next_stock_amount(stock_vars, i))
            string_vec_append(vec, " ");
    }
    if (*amount > 0) {
        string_vec_append(vec, ",");
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

static void send_look_message(server_t *server, string_vec_t *vec)
{
    char *buffer = string_vec_str(vec);
    dprintf(CLIENT->fd, "%s" ZMSG_END_SEQ, buffer);
    free(buffer);
}

void command_look(server_t *server)
{
    string_vec_t *vec = string_vec_init();
    struct look_coordinates_s coordinates = {
        .xStart = CLIENT->tile->x,
        .xEnd = CLIENT->tile->x,
        .yStart = CLIENT->tile->y,
        .yEnd = CLIENT->tile->y,
    };
    tile_t *tile = NULL;
    unsigned int amount;

    if (vec == NULL)
        return;
    amount = get_amount_of_tiles(server);
    string_vec_append(vec, "[");
    buffer_add_tile_stock(server, vec, CLIENT->tile, &amount);
    for (unsigned int level = 1; level <= CLIENT->level; level++) {
        move_coordinates(&coordinates, CLIENT->direction);
        for (int y = coordinates.yStart; y <= coordinates.yEnd; y++) {
            for (int x = coordinates.xStart; x <= coordinates.xEnd; x++) {
                tile = world_get_wrapped_tile(server->world, x, y);
                buffer_add_tile_stock(server, vec, tile, &amount);
            }
        }
    }
    string_vec_append(vec, " ]");
    send_look_message(server, vec);
    string_vec_free(vec);
}
