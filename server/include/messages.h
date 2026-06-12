#ifndef ZAPPY_SERVER_MESSAGES_H_
    #define ZAPPY_SERVER_MESSAGES_H_

    #include <unistd.h> // IWYU pragma: keep
    #include <string.h> // IWYU pragma: keep

    #define ZMSG_END_SEQ "\n"

    #define ZMSG_WELCOME "WELCOME" ZMSG_END_SEQ
    #define ZMSG_OK "ok" ZMSG_END_SEQ
    #define ZMSG_KO "ko" ZMSG_END_SEQ

    #define WRITE_MESSAGE(fd, msg) write(fd, msg, strlen(msg))

#endif
