from ..AgenticIntelligenceKpiWorkflow import Freakster, Role
from .Perroquet import Perroquet
import re

class Commando(Perroquet):
    def mainloop(self):
        print("Commando created: Attack Protocol Initialized")
        self.findEnemies()
        while True:
            self.Forward()
            self.Eject()

    def findEnemies(self):
        while True:
            self.Look()
            if self.vision[1][1].get("player") and self.vision[1][1]["player"] >= 4:
                break
            self.Right()
