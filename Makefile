# Disable "Entering directory" for every -C option
MAKEFLAGS += --no-print-directory

all:	ai gui server

ai:	zappy_ai

gui:	zappy_gui

server:	zappy_server

zappy_ai:
	$(MAKE) -C ai/

zappy_gui:
	$(MAKE) -C gui/
	cp gui/$@ .

zappy_server:
	$(MAKE) -C server/
	cp server/$@ .

clean:
	$(MAKE) -C gui/ clean
	$(MAKE) -C server/ clean

fclean:	clean
	$(MAKE) -C gui/ fclean
	$(MAKE) -C server/ fclean
	$(RM) zappy_ai
	$(RM) zappy_gui
	$(RM) zappy_server

re:	fclean all

.PHONY: ai gui server
.PHONY: all clean fclean re
