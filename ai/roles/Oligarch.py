from ..AgenticIntelligenceKpiWorkflow import Freakster, Role, OLIGARCH_STASH


class Oligarch(Freakster):

    def mainloop(self):
        create_explorer = 1
        self.Look()
        nb_player = self.vision[0][0]["player"]
        if (nb_player <= 2):
            self.Fork(Role.OLIGARCH)
            self.Fork(Role.FOOD_FACTORY)
        elif (nb_player <= 4):
            self.Fork(Role.OLIGARCH)
        while (True):
            if (create_explorer % 2 == 0):
                self.Fork(Role.SACRIFICE)
            else:
                self.Fork(Role.EXPLORER)
            create_explorer += 1
            self.Inventory()
            while (self.inv["food"] < OLIGARCH_STASH):
                if (not self.Take("food")):
                    break
