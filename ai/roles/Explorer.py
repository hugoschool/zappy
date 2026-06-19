from ..AgenticIntelligenceKpiWorkflow import Freakster, Direction, Role
from random import randint

class Explorer(Freakster):
    def __init__(self, socket, toAdd):
        super().__init__(socket, toAdd)
        self.pos_x = 0
        self.pos_y = 0
    objective = {"linemate": 100, "deraumere": 100, "sibur": 100,
                 "mendiane": 100, "phiras": 100, "thystame": 100}
    treshold = {}

    def mainloop(self):
        self.Look()
        self.gloutonTypeShit()

    def gloutonTypeShit(self):
        while True:
            idx = 1
            maxVal = -1
            val = []

            self.Inventory()
            if self.inv["food"] <= 3:
                self.returnKremlin()
            if len(self.vision) < 2:
                self.Look()
            for i in self.vision[1]:
                val.append(self.getValue(i))
            for i in range(len(val)):
                if val[i] > maxVal:
                    maxVal = val[i]
                    idx = i
            if (maxVal == 0):
                idx = randint(0, 2)
            cache = self.vision
            if idx == 1:
                self.Forward()
            elif idx == 0:
                self.Left()
                self.Forward()
                self.Right()
                self.Forward()
            else:
                self.Right()
                self.Forward()
                self.Left()
                self.Forward()
            if (len(cache) == 1):
                self.takeItems({})
            else:
                self.takeItems(cache[1][idx])
            self.Look()

    def takeItems(self, dic):
        for (obj, value) in dic.items():
            if obj == "player":
                continue
            for i in range(value):
                if obj != "food" and self.objective[obj] > 0:
                    self.Take(obj)
                    if obj != "food":
                        self.objective[obj] = self.objective[obj] - 1

    def getValue(self, dic):
        val = 0
        if dic.get("player"):
            return -1
        for (key, value) in dic.items():
            if key != "food" and self.objective[key] > 0:
                val += value
        return val

    def returnKremlin(self):
        # go back to base
        if self.pos_x < 0:
            while self.direction != Direction.RIGHT:
                self.Right()
        else:
            while self.direction != Direction.LEFT:
                self.Left()
        while self.pos_x != 0:
            self.Forward()

        if self.pos_y < 0:
            while self.direction != Direction.UP:
                self.Left()
        else:
            while self.direction != Direction.DOWN:
                self.Right()
        while self.pos_y != 0:
            self.Forward()

        # refills and drop
        for i in range(15):
            self.Take("food")
        self.Fork(Role.SACRIFICE)
        for (key, value) in self.inv.items():
            if key != "food":
                for i in range(value):
                    self.Set(key)
        return
