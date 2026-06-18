from ..AgenticIntelligenceKpiWorkflow import Freakster, Role


class FoodFactory(Freakster):
    def mainloop(self):
        while (True):
            self.Fork(Role.SACRIFICE)
            self.Inventory()
            if (self.inv["food"] < 10):
                if (not self.Take("food")):
                    break