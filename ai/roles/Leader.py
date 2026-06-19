from ..AgenticIntelligenceKpiWorkflow import Freakster, Role

REQUIREMENTS = [
    {"linemate": 1},
    {"linemate": 1, "deraumere": 1, "sibur": 1},
    {"linemate": 2, "sibur": 1, "phiras": 2},
    {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
    {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
    {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
    {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
    ]

class Leader(Freakster):
    def __init__(self, socket, toAdd):
        self.level = 1
        super().__init__(socket, toAdd)

    def mainloop(self):
        self.Fork(Role.OLIGARCH)
        self.Fork(Role.OLIGARCH)
        self.Fork(Role.FOOD_FACTORY)
        while (True):
            self.Fork(Role.EXPLORER)
            self.Inventory()
            while (self.inv["food"] < 10):
                if (not self.Take("food")):
                    break
            self.Look()
            can_incantate = True
            for elem in REQUIREMENTS[self.level - 1]:
                if elem not in self.vision[0][0] or self.vision[0][0][elem] < REQUIREMENTS[self.level - 1][elem]:
                    can_incantate = False
            if can_incantate:
                self.Incantation()