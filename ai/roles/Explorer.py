from ..AgenticIntelligenceKpiWorkflow import Freakster, Direction, Role
from random import randint

EXPLORER_STASH = 15

class Explorer(Freakster):
    def __init__(self, socket, toAdd):
        super().__init__(socket, toAdd)
        self.pos_x = 0
        self.pos_y = 0

    def mainloop(self):
        self.Forward()
        self.Forward()
        self.Look()
        self.gloutonTypeShit()

    def should_go_back(self):
        if self.inv["food"] <= 5: #5 à revoir dans le futur
            return True
        return False

    def gloutonTypeShit(self):
        while True:
            idx = 1
            maxVal = -1
            val = []

            self.Inventory()
            if self.should_go_back():
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
            if (len(cache) != 1):
                self.takeItems(cache[1][idx])
            self.Look()

    def takeItems(self, dic):
        if (dic.get("player") and dic["player"] >= 8):
            return
        for (obj, value) in dic.items():
            if obj == "player":
                continue
            for i in range(value):
                if obj != "food":
                    self.Take(obj)

    def getValue(self, dic):
        val = 0
        if dic.get("player"):
            return -1
        for (key, value) in dic.items():
            if key != "food":
                val += value
        return val

    def returnKremlin(self):
        # go back to base
        if self.pos_x < 0 and self.pos_x <= self.map_dim[0]:
            while self.direction != Direction.RIGHT:
                self.Right()
        else:
            while self.direction != Direction.LEFT:
                self.Left()
        while self.pos_x != 0:
            self.Forward()

        if self.pos_y < 0 and self.pos_y <= self.map_dim[1]:
            while self.direction != Direction.UP:
                self.Left()
        else:
            while self.direction != Direction.DOWN:
                self.Right()
        while self.pos_y != 0:
            self.Forward()

        # refills and drop
        self.Inventory()
        while (self.Take("food") and self.inv["food"] <= EXPLORER_STASH):
            pass
        # self.Fork(Role.SACRIFICE)
        for (key, value) in self.inv.items():
            if key != "food":
                for i in range(value):
                    self.Set(key)
        self.Forward()
        self.Forward()
        return
