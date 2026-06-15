#ifndef ZAPPY_SERVER_LEVEL_H_
    #define ZAPPY_SERVER_LEVEL_H_

    #include "server.h"

    #define MAX_LEVEL 8

// Level one
bool level_one_condition(server_t *server);
void level_one_consume(stock_t *stock);

// Level two
bool level_two_condition(server_t *server);
void level_two_consume(stock_t *stock);

// Level three
bool level_three_condition(server_t *server);
void level_three_consume(stock_t *stock);

// Level four
bool level_four_condition(server_t *server);
void level_four_consume(stock_t *stock);

// Level five
bool level_five_condition(server_t *server);
void level_five_consume(stock_t *stock);

// Level six
bool level_six_condition(server_t *server);
void level_six_consume(stock_t *stock);

// Level seven
bool level_seven_condition(server_t *server);
void level_seven_consume(stock_t *stock);

typedef struct {
    unsigned int level;
    bool (*condition)(server_t *);
    void (*consume)(stock_t *);
} level_condition_t;

static const level_condition_t conditions[MAX_LEVEL - 1] = {
    {1, &level_one_condition, &level_one_consume},
    {2, &level_two_condition, &level_two_consume},
    {3, &level_three_condition, &level_three_consume},
    {4, &level_four_condition, &level_four_consume},
    {5, &level_five_condition, &level_five_consume},
    {6, &level_six_condition, &level_six_consume},
    {7, &level_seven_condition, &level_seven_consume},
};

bool level_up_possibility(server_t *server);
bool level_up(server_t *server);

#endif
