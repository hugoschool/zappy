#include "level.h"
#include "clients.h"
#include "server.h"

bool level_up_possibility(server_t *server)
{
    for (size_t i = 0; i < MAX_LEVEL - 1; i++) {
        if (CLIENT->level == conditions[i].level && conditions[i].condition(server))
            return true;
    }
    return false;
}

// Returns true on a successful level up, false if it fails
bool level_up(server_t *server)
{
    for (size_t i = 0; i < MAX_LEVEL - 1; i++) {
        if (CLIENT->level == conditions[i].level && conditions[i].condition(server)) {
            conditions[i].consume(&CLIENT->stock);
            CLIENT->level++;
            if (CLIENT->level == 8) {
                CLIENT->team->max_nb_player_lvl_8 += 1;
            }
            return true;
        }
    }
    return false;
}
