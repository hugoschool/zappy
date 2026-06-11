#include "dynamic_arrays.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

static size_t string_split_intern(string_vec_t *vec, char *str, char *del)
{
    size_t amount = 0;
    char *token = strtok(str, del);

    while (token != NULL) {
        if (vec != NULL)
            DA_APPEND(vec, strdup(token));
        amount++;
        token = strtok(NULL, del);
    }
    return amount;
}

string_vec_t *string_split(char *str, char *del)
{
    string_vec_t *vec = string_vec_init();

    if (vec == NULL)
        return NULL;
    string_split_intern(vec, str, del);
    return vec;
}

size_t string_split_amount(char *str, char *del)
{
    return string_split_intern(NULL, str, del);
}
