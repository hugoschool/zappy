from ..AgenticIntelligenceKpiWorkflow import Freakster, Role


class Oligarch(Freakster):
    def __init__(self, socket, toAdd):
        self.level = 1
        super().__init__(socket, toAdd)

    def mainloop(self):
        self.Look()
        nb_player = self.vision[0][0]["player"]
        if (nb_player <= 2):
            self.Fork(Role.OLIGARCH)
            self.Fork(Role.FOOD_FACTORY)
        elif (nb_player <= 4):
            self.Fork(Role.OLIGARCH)
        while (True):
            self.Fork(Role.EXPLORER)
            self.Inventory()
            while (self.inv["food"] < 10):
                if (not self.Take("food")):
                    break