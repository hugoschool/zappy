#include "buffer.h"
#include "messages.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

circular_buffer_t *cb_init(void)
{
    circular_buffer_t *cb = malloc(sizeof(circular_buffer_t));

    if (cb == NULL)
        return NULL;
    cb->amount = 0;
    cb->size = MAX_COMMANDS_AMOUNT;
    cb->buffer_size = BUFFER_SIZE;
    cb->index = 0;
    cb->head = 0;
    cb->tail = 0;
    for (size_t i = 0; i < cb->size; i++) {
        memset(cb->commands[i], 0, BUFFER_SIZE);
    }
    return cb;
}

void cb_free(circular_buffer_t *cb)
{
    if (cb == NULL)
        return;
    free(cb);
}

void cb_push_buffer(circular_buffer_t *cb, char *str)
{
    if (cb->amount >= cb->size) {
        // Do not add current buffer, wait for commands to be unqueued.
        return;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        cb->commands[cb->tail][cb->index] = str[i];
        cb->index = (cb->index + 1) % cb->buffer_size;
    }
    if (strstr(cb->commands[cb->tail], ZMSG_END_SEQ) != NULL) {
        cb->tail = (cb->tail + 1) % cb->size;
        cb->amount++;
        cb->index = 0;
    }
}

char *cb_pop_delimiter(circular_buffer_t *cb)
{
    char *str = NULL;

    if (cb->amount == 0)
        return NULL;
    str = cb->commands[cb->head];
    remove_ending_seq(str);
    cb->head = (cb->head + 1) % cb->size;
    cb->amount--;
    return str;
}
