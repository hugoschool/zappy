#include "buffer.h"
#include "messages.h"
#include <string.h>

void cb_push_buffer(circular_buffer_t *cb, char *str)
{
    if (cb->amount >= cb->size) {
        // Do not add current buffer, wait for commands to be unqueued.
        return;
    }
    if (cb->new_tail) {
        memset(cb->commands[cb->tail], 0, BUFFER_SIZE);
        cb->new_tail = false;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        cb->commands[cb->tail][cb->index] = str[i];
        cb->index = (cb->index + 1) % cb->buffer_size;
        if (strncmp(&str[i], ZMSG_END_SEQ, strlen(ZMSG_END_SEQ)) == 0) {
            cb->tail = (cb->tail + 1) % cb->size;
            cb->amount++;
            cb->new_tail = true;
            cb->index = 0;

            // Hit the limit of the amount of commands that can be held
            if (cb->amount >= cb->size)
                return;
        }
    }
}
