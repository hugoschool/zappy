from ..AgenticIntelligenceKpiWorkflow import Freakster
from ..Communication import SocketReceiveError

class Sacrifice(Freakster):
    def mainloop(self):
        self.Set("food")
        while (True):
            self.Look()
            if ("player" in self.vision[1][1] and self.vision[1][1]["player"] >= 6):
                self.Forward()
                break
            self.Right()
        for i in range(9):
            self.Set("food")
        raise SocketReceiveError("Tactical Suicide")