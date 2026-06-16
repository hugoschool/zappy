from ..AgenticIntelligenceKpiWorkflow import Freakster, Role


class Oligarch(Freakster):
    def __init__(self, x, y, socket, toAdd):
        self.nb_spawned = 0
        super().__init__(x, y, socket, toAdd)

    def mainloop(self):
        self.Look()
        while (True):
            self.Fork(Role.EXPLORER)
            self.Inventory()
            while (self.inv["food"] < 10):
                self.Take("food")