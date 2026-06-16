#include <stdlib.h>
#include <string.h>

int get_player_nb(char *str)
{
    if (strlen(str) < 2 || str[0] != '#')
        return -1;
    return atoi(&str[1]);
}
