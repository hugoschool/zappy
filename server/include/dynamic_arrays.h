#ifndef ZAPPY_SERVER_DYNAMIC_ARRAYS_H_
    #define ZAPPY_SERVER_DYNAMIC_ARRAYS_H_

    #include <stdio.h> // IWYU pragma: keep
    #include <stdlib.h> // IWYU pragma: keep

    #define INITIAL_SIZE 256

// For all dynamic arrays:
// elems: all the elements contained in the array
// amount: current amount of elements in the array
// size: actual malloc'd size of the array

#define DA_INIT(da, type)   \
    da->elems = calloc(INITIAL_SIZE, sizeof(type)); \
    da->amount = 0; \
    da->size = INITIAL_SIZE;

#define DA_FREE(da, func)   \
    for (size_t i = 0; i < da->amount; i++) {   \
        func(da->elems[i]); \
    }   \
    free(da->elems);    \
    free(da);

#define DA_RESIZE(da) \
    if (da->amount == da->size) { \
        da->size *= 2; \
        da->elems = realloc(da->elems, sizeof(da->elems[0]) * (da->size));  \
        if (da->elems == NULL) {   \
            perror("realloc");  \
            exit(84);   \
        }   \
    }

#define DA_APPEND(da, elem) \
    DA_RESIZE(da);  \
    da->elems[da->amount] = elem;   \
    da->amount++;

#endif
