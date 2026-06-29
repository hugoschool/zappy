#include "args.h"
#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Inspired by the subject reference server
void print_help(void)
{
    printf(
    "USAGE:\n"
    "   ./zappy_server -p port -x width -y height -n name1 name2 ... -c client_nb -f freq\n"
    "       port            Port number (ex: 4242)\n"
    "       width           Width of the world (must be >0)\n"
    "       height          Height of the world (must be >0)\n"
    "       nameX           Name of the team X\n"
    "       client_nb       Number of authorized clients per team (must be >0)\n"
    "       freq            Reciprocal of time unit for execution of actions (must be >0)\n"
    );
}

int main(int argc, char *argv[])
{
    args_t *args = parse_args(argc, argv);

    if (args == NULL || args->valid == false) {
        print_help();
        args_free(args);
        return 84;
    }
    srand(time(NULL));
    zappy_server(args);
    args_free(args);
    return 0;
}
