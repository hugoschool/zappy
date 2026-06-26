#include "buffer.h"
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
    // No need to set it to true as we're already setting all buffers to zero
    cb->new_tail = false;
    for (size_t i = 0; i < cb->size; i++) {
        memset(cb->commands[i], 0, BUFFER_SIZE);
    }
    return cb;
}
