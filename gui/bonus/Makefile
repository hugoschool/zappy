CXX	:=  clang++
CXXFLAGS    :=  -Wall -Wextra -std=c++20
CPPFLAGS	:=	-I ./include -I ../include
LDFLAGS	:=	-lraylib

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-g3
endif

ifeq ($(ENV), dev-asan)
	CXXFLAGS	+=	-fsanitize=address
	LDLIBS	+=	-fsanitize=address
endif

SRC :=  src/main.cpp	\
		src/Zappy.cpp \
		src/Commands.cpp \
		src/RaylibBonus.cpp \
		../src/Utils.cpp	\
		../src/Parser.cpp	\
		../src/Socket.cpp	\
		../src/ANetwork.cpp	\
		../src/Communication.cpp	\
		../src/Commands.cpp	\
		../src/Zappy.cpp	\
		../src/Map.cpp		\
		../src/Tile.cpp	\
		../src/Raylib.cpp	\
		../src/RaylibParticles.cpp	\
		../src/TextureUtilityFinderFiller3000.cpp	\
		../src/GameplayEntitiesHolder.cpp	\
		../src/ModelHolder.cpp	\
		../src/Protocol.cpp \
		../src/APlayer.cpp \
		../src/Egg.cpp \
		../src/PlayerInfo.cpp \
		../src/entities/AEntity.cpp	\
		../src/entities/Food.cpp	\
		../src/entities/Materials.cpp

OBJ :=  $(SRC:.cpp=.o)

BINARY  :=  zappy_gui_bonus

all:    $(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(BINARY)

re: fclean all

.PHONY: all clean fclean re
