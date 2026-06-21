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
		src/world.c \
		src/stock.c \
		src/frequency.c \
		src/players.c \
		src/buffer.c \
		src/level.c

# Levels
SRC	+=	src/levels/one.c \
		src/levels/two.c \
		src/levels/three.c \
		src/levels/four.c \
		src/levels/five.c \
		src/levels/six.c \
		src/levels/seven.c

# Utils source
SRC	+=	src/utils/remove_ending_seq.c \
		src/utils/strcmp_end.c \
		src/utils/get_player_nb.c \
		src/utils/string_vec/free.c \
		src/utils/string_vec/init.c \
		src/utils/string_vec/append.c \
		src/utils/string_vec/str.c \
		src/utils/string_vec/split.c

# Commands source
SRC	+=	src/commands/handler.c \
		src/commands/left.c \
		src/commands/right.c \
		src/commands/inventory.c \
		src/commands/take.c \
		src/commands/set.c \
		src/commands/connect_nbr.c \
		src/commands/fork.c \
		src/commands/forward.c \
		src/commands/incantation.c \
		src/commands/look.c \
		src/commands/eject.c \
		src/commands/broadcast.c \
		src/commands/graphical/msz.c \
		src/commands/graphical/mct.c \
		src/commands/graphical/tna.c \
		src/commands/graphical/ppo.c \
		src/commands/graphical/plv.c \
		src/commands/graphical/pin.c \
		src/commands/graphical/sgt.c \
		src/commands/graphical/sst.c \
		src/commands/graphical/smg.c \
		src/commands/graphical/pnw.c \
		src/commands/graphical/enw.c \
		src/commands/graphical/ebo.c \
		src/commands/graphical/pex.c \
		src/commands/graphical/pdr.c \
		src/commands/graphical/pgt.c \
		src/commands/graphical/pbc.c \
		src/commands/graphical/pfk.c \
		src/commands/graphical/seg.c \
		src/commands/graphical/edi.c \
		src/commands/graphical/pdi.c \
		src/commands/graphical/pie.c \
		src/commands/graphical/pic.c \
		src/commands/graphical/bct.c

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
