from ..AgenticIntelligenceKpiWorkflow import Freakster
from ..Communication import SocketReceiveError


class Sacrifice(Freakster):
    def mainloop(self):
        for i in range(10):
            self.Set("food")
        raise SocketReceiveError("Tactical Suicide")