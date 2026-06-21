#ifndef ZAPPY_SERVER_BUFFER_H_
    #define ZAPPY_SERVER_BUFFER_H_

    #include <stddef.h>
    #include <stdbool.h>
    #include <stdlib.h>

    #define MAX_COMMANDS_AMOUNT 10

    // Maximum line length (man 3 termios)
    #define BUFFER_SIZE 4096

typedef struct circular_buffer_s {
    char commands[MAX_COMMANDS_AMOUNT][BUFFER_SIZE];

    // Same as dynamic_arrays
    // amount: current amount of buffer
    // size: represents the maximum amount of commands that can be handled
    size_t amount;
    size_t size;

    // Maximum buffer size, set automatically by BUFFER_SIZE macro
    size_t buffer_size;

    // Current index of the current buffer being handled
    size_t index;
    // Is this the first write to the tail?
    // Used to reset the current buffer of the tail
    bool new_tail;

    // Current command being read
    size_t head;
    // Current command being written
    size_t tail;
} circular_buffer_t;

circular_buffer_t *cb_init(void);
void cb_free(circular_buffer_t *cb);
void cb_push_buffer(circular_buffer_t *cb, char *str);
char *cb_pop_delimiter(circular_buffer_t *cb);

#endif
