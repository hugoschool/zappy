#include "buffer.h"

void cb_free(circular_buffer_t *cb)
{
    if (cb == NULL)
        return;
    free(cb);
}
