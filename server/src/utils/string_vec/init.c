#include "dynamic_arrays.h"
#include "utils.h"
#include <stdlib.h>

string_vec_t *string_vec_init(void)
{
    string_vec_t *vec = malloc(sizeof(string_vec_t));

    if (vec == NULL)
        return NULL;
    DA_INIT(vec, char *);
    if (vec->elems == NULL)
        return NULL;
    return vec;
}
