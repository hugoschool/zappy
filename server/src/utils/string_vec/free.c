#include "dynamic_arrays.h"
#include "utils.h"
#include <stdlib.h>

void string_vec_free(string_vec_t *vec)
{
    if (vec == NULL)
        return;
    DA_FREE(vec, free);
}
