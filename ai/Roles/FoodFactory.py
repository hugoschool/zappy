from ..AgenticIntelligenceKpiWorkflow import Freakster


class FoodFactory(Freakster):
    def mainloop(self):
        self.Fork()
        if (self.Inventory["food"] < 3):
            self.Take("food")
            self.Take("food")
            self.Take("food")