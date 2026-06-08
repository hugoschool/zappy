#include "args.h"
#include "dynamic_arrays.h"
#include <bits/getopt_core.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

static args_t *args_init()
{
    args_t *args = calloc(1, sizeof(args_t));

    if (args == NULL)
        return NULL;
    args->names = malloc(sizeof(args_team_names_t));
    if (args->names == NULL)
        return NULL;
    DA_INIT(args->names, char *);
    if (args->names->elems == NULL)
        return NULL;
    args->valid = true;
    return args;
}

void args_free(args_t *args)
{
    if (args == NULL)
        return;
    DA_FREE(args->names, free);
    free(args);
}

static void parse_getopt_arg(args_t *args, int argc, char *argv[], int c)
{
    if (optind >= argc)
        return;
    switch (c) {
        case 'p':
            args->port = atoi(argv[optind]);
            break;
        case 'x':
            args->x = atoi(argv[optind]);
            break;
        case 'y':
            args->y = atoi(argv[optind]);
            break;
        case 'n':
            optind--;
            for (; optind < argc && *argv[optind] != '-'; optind++) {
                DA_APPEND(args->names, strdup(argv[optind]));
            }
            break;
        case 'c':
            args->clients = atoi(argv[optind]);
            break;
        case 'f':
            args->freq = atoi(argv[optind]);
            break;
        default:
            break;
    }
}

static void verify_args(args_t *args)
{
    if (args->port <= 0) {
        args->valid = false;
        return;
    }
    if (args->x <= 0 || args->y <= 0) {
        args->valid = false;
        return;
    }
    if (args->clients <= 0) {
        args->valid = false;
        return;
    }
    if (args->freq <= 0) {
        args->valid = false;
        return;
    }
}

args_t *parse_args(int argc, char *argv[])
{
    int c;
    args_t *args = args_init();

    if (args == NULL)
        return NULL;
    while ((c = getopt(argc, argv, OPT_ARGUMENTS)) != -1) {
        parse_getopt_arg(args, argc, argv, c);
    }
    verify_args(args);
    return args;
}
