CC	?=	clang
CFLAGS	:=	-Wall -Wextra -std=gnu17
CPPFLAGS	:=	-I ../../include

AR	?=	ar

ifeq ($(ENV), dev)
	CFLAGS	+=	-g3
endif

# Shared between all buffer implementations
SRC	:=	# Left intentionally empty

# Circular buffer
SRC	+=	circular/init.c \
		circular/free.c \
		circular/push.c \
		circular/pop.c \
		\
		../utils/remove_ending_seq.c

OBJ	:=	$(SRC:.c=.o)

BINARY	:=	libbuffer.a

all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(AR) rc $@ $^

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
