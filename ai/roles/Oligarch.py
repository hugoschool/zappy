from ..AgenticIntelligenceKpiWorkflow import Freakster, Role, OLIGARCH_STASH


class Oligarch(Freakster):

    def mainloop(self):
        self.Look()
        nb_player = self.vision[0][0]["player"]
        if (nb_player <= 2):
            self.Fork(Role.OLIGARCH)
            self.Fork(Role.FOOD_FACTORY)
        elif (nb_player <= 4):
            self.Fork(Role.OLIGARCH)
        self.Fork(Role.SPETSNAZ)
        self.Fork(Role.EXPLORER)
        self.Fork(Role.EXPLORER)
        self.Fork(Role.EXPLORER)
        # on pourrait faire un dernier fork, mais après les oligarques ont moins le temps de prendre
        # de la bouffe et donc ça peut être un peu dangereux
        while (True):
            self.Inventory()
            while (self.inv["food"] < OLIGARCH_STASH):
                if (not self.Take("food")):
                    break

