from ..AgenticIntelligenceKpiWorkflow import Freakster, Role
from .Explorer import Explorer


class Spetsnaz(Explorer):
    def __init__(self, socket, toAdd):
        super().__init__(socket, toAdd)

    def mainloop(self):
        self.Forward()
        self.Look()
        self.gloutonTypeShit()
