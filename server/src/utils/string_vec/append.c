#include "dynamic_arrays.h"
#include "utils.h"
#include <string.h>

// Uses strdup for "safe" append and free control.
// No strdup: use unsafe_append
void string_vec_append(string_vec_t *vec, char *str)
{
    DA_APPEND(vec, strdup(str));
}

// WARNING: you are giving COMPLETE control of the given parameter to the string_vec_t which
// WILL automatically free the string on free of the string_vec.
void string_vec_unsafe_append(string_vec_t *vec, char *str)
{
    DA_APPEND(vec, str);
}
