from ..AgenticIntelligenceKpiWorkflow import Freakster
from ..Communication import SocketReceiveError

class Sacrifice(Freakster):
    def mainloop(self):
        self.Set("food")
        for _ in range(4):
            try:
                self.Look()
                if "player" in self.vision[1][1] and self.vision[1][1]["player"] >= 6:
                    self.Forward()
                    break
                self.Right()
            except IndexError as e:
                print(f"Sacrifice vision: {self.vision} | {e}")
        for _ in range(9):
            self.Set("food")
        raise SocketReceiveError("Tactical Suicide")
