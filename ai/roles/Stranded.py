from ..AgenticIntelligenceKpiWorkflow import Freakster, Direction, Role, CALL_MESSAGE
from .Explorer import Explorer
from random import randint

class Stranded(Explorer):
    def __init__(self, socket, toAdd):
        super().__init__(socket, toAdd)
        self.pos_x = -1
        self.pos_y = -1
        self.is_home_found = False

    def mainloop(self):
        self.Look()
        self.gloutonTypeShit()

    def handleBroadcast(self):
        tile,message = super().handleBroadcast()
        if (message == CALL_MESSAGE):
            pass
