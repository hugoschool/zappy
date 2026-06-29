from ..AgenticIntelligenceKpiWorkflow import Freakster, Role
from .Explorer import Explorer

class Spetsnaz(Explorer):
    def __init__(self, socket, toAdd):
        super().__init__(socket, toAdd)
        self.step = 0

    def should_go_back(self):
        if self.step == 0 and self.inv["linemate"] >= 1:
            self.step += 1
            return True
        if self.step == 1 and (self.inv["deraumere"] >= 1 or self.inv["sibur"] >= 1):
            self.step += 1
            return True
        return super().should_go_back()

    def getValue(self, dic):
        val = 0
        if dic.get("player"):
            return -1
        for (key, value) in dic.items():
            if self.step == 0 and key == "linemate":
                return 100 # grande valeur pour forcer d'aller sur cette case
            if self.step == 1 and (key == "sibur" or key == "deraumere"):
                return 100
            if key != "food":
                val += value
        return val