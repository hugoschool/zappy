#include "buffer.h"
#include "utils.h"

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
