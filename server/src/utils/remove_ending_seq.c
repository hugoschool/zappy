#include "messages.h"
#include "utils.h"
#include <string.h>

void remove_ending_seq(char *str)
{
    size_t len = 0;

    if (strcmp_end(str, ZMSG_END_SEQ) != 0)
        return;
    len = strlen(str);
    for (size_t i = 0; i < strlen(ZMSG_END_SEQ); i++) {
        str[len - (i + 1)] = 0;
    }
}
