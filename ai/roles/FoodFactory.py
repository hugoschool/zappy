from ..AgenticIntelligenceKpiWorkflow import Freakster, Role, OLIGARCH_STASH


class FoodFactory(Freakster):
    def mainloop(self):
        self.Forward()
        while (True):
            self.Fork(Role.SACRIFICE)
            self.Inventory()
            while (self.inv["food"] < OLIGARCH_STASH):
                if (not self.Take("food")):
                    break