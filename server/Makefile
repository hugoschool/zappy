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
		src/socket.c

# Commands source
SRC	+=	src/commands/handler.c

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
