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
    def __init__(self, x, y, socket, toAdd):
        self.level = 1
        super().__init__(x, y, socket, toAdd)

    def mainloop(self):
        self.Fork(Role.OLIGARCH)
        self.Fork(Role.OLIGARCH)
        self.Fork(Role.FOOD_FACTORY)
        while (True):
            self.Fork(Role.EXPLORER)
            self.Inventory()
            while (self.inv["food"] < 10):
                self.Take("food")
            self.Look()
            if (self.vision[0])
