CC	?=	clang
CFLAGS	:=	-Wall -Wextra -std=gnu17
CPPFLAGS	:=	-I ./include

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
endif

SRC	:=	src/main.c \
		src/args.c \
		src/clients.c \
		src/poll.c \
		src/poller.c \
		src/server.c \
		src/socket.c \
		src/teams.c \
		src/world.c

# Utils source
SRC	+=	src/utils/remove_ending_seq.c \
		src/utils/strcmp_end.c

# Commands source
SRC	+=	src/commands/handler.c \
		src/commands/graphical/msz.c

OBJ	:=	$(SRC:.c=.o)

BINARY	:=	zappy_server

all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(CC) -o $(BINARY) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
