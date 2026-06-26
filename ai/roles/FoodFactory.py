from ..AgenticIntelligenceKpiWorkflow import Freakster, Role, OLIGARCH_STASH


class FoodFactory(Freakster):
    def mainloop(self):
        self.Forward()
        while (True):
            self.Fork(Role.SACRIFICE)
            self.Inventory()
            if (self.inv["food"] < OLIGARCH_STASH):
                self.Take("food")