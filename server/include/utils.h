#ifndef ZAPPY_SERVER_UTILS_H_
    #define ZAPPY_SERVER_UTILS_H_

    #include <stddef.h>

typedef struct {
    char **elems;
    size_t amount;
    size_t size;
} string_vec_t;

string_vec_t *string_vec_init(void);
string_vec_t *string_split(char *str, char *del);
int string_split_amount(char *str, char *del);
void string_vec_free(string_vec_t *vec);

int strcmp_end(const char *str, const char *end);
void remove_ending_seq(char *str);

#endif
