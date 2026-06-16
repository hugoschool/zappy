from ..AgenticIntelligenceKpiWorkflow import Freakster, Role


class FoodFactory(Freakster):
    def mainloop(self):
        self.Fork(Role.SACRIFICE)
        self.Inventory()
        if (self.inv["food"] < 10):
            self.Take("food")
