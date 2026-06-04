CXX	:=  clang++
CXXFLAGS    :=  -Wall -Wextra -std=c++20
CPPFLAGS	:=	-I ./include

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-g3
endif

ifeq ($(ENV), dev-asan)
	CXXFLAGS	+=	-fsanitize=address
	LDLIBS	+=	-fsanitize=address
endif

SRC :=  src/main.cpp	\
		src/Utils.cpp	\
		src/Parser.cpp

OBJ :=  $(SRC:.cpp=.o)

BINARY  :=  zappy_gui

all:    $(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(BINARY)

re: fclean all

.PHONY: all clean fclean re
