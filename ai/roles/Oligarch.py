from ..AgenticIntelligenceKpiWorkflow import Freakster, Role


class Oligarch(Freakster):
    def __init__(self, x, y, socket, toAdd):
        self.nb_spawned = 0
        super().__init__(x, y, socket, toAdd)

    def mainloop(self):
        if (self.nb_spawned < 3):
            self.Fork(Role.FOOD_FACTORY)
            self.nb_spawned += 1
        else:
            self.Fork(Role.SACRIFICE)
        if (self.inv["food"] < 3):
            self.Take("food")
            self.Take("food")
            self.Take("food")
