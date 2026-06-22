from ..AgenticIntelligenceKpiWorkflow import Freakster, Role, OLIGARCH_STASH

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

    def mainloop(self):
        self.Fork(Role.OLIGARCH)
        self.Fork(Role.OLIGARCH)
        self.Fork(Role.FOOD_FACTORY)
        self.Fork(Role.EXPLORER)
        while (True):
            self.Fork(Role.EXPLORER)
            self.Inventory()
            while (self.inv["food"] < OLIGARCH_STASH):
                if (not self.Take("food")):
                    break
            self.Look()
            can_incantate = True
            for elem in REQUIREMENTS[self.level - 1]:
                if elem not in self.vision[0][0] or self.vision[0][0][elem] < REQUIREMENTS[self.level - 1][elem]:
                    print(f"cannot incantate: Need {REQUIREMENTS[self.level - 1][elem]} {elem} for advancement to lvl {self.level + 1}")
                    can_incantate = False
            if can_incantate:
                self.Incantation()
