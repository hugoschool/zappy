#include "args.h"
#include "server.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    args_t *args = parse_args(argc, argv);

    if (args == NULL || args->valid == false) {
        args_free(args);
        return 84;
    }
    zappy_server(args);
    args_free(args);
    return 0;
}
