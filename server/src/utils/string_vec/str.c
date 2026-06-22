#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static size_t string_vec_strlen(string_vec_t *vec)
{
    size_t size = 0;

    for (size_t i = 0; i < vec->amount; i++) {
        size += strlen(vec->elems[i]);
    }
    return size;
}

char *string_vec_str(string_vec_t *vec)
{
    size_t size = string_vec_strlen(vec) + 1;
    char *str = calloc(size, sizeof(char));

    for (size_t i = 0; i < vec->amount; i++) {
        strcat(str, vec->elems[i]);
    }
    return str;
}
