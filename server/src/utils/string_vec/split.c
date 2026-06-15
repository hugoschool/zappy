#include "utils.h"
#include <stdlib.h>
#include <string.h>

static int string_split_intern(string_vec_t *vec, char *og_str, char *del)
{
    size_t amount = 0;
    char str[strlen(og_str) + 1];
    char *saveptr = NULL;
    char *token = NULL;

    memset(str, 0, strlen(og_str) + 1);
    strncpy(str, og_str, strlen(og_str));
    token = strtok_r(str, del, &saveptr);
    while (token != NULL) {
        if (vec != NULL) {
            string_vec_append(vec, token);
        }
        amount++;
        token = strtok_r(NULL, del, &saveptr);
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

int string_split_amount(char *str, char *del)
{
    return string_split_intern(NULL, str, del);
}
