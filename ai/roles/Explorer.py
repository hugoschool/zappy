from random import randint
from ..AgenticIntelligenceKpiWorkflow import Freakster, Direction, Role

EXPLORER_STASH = 15

class Explorer(Freakster):
    def __init__(self, socket, toAdd):
        super().__init__(socket, toAdd)
        self.pos_x = 0
        self.pos_y = 0

    def mainloop(self):
        self.Forward()
        self.Forward()
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

            self.Look()
            self.Inventory()
            if self.should_go_back():
                self.returnKremlin()
                continue

            for i in self.vision[1]:
                val.append(self.getValue(i))

            for i in range(len(val)):
                if val[i] > maxVal:
                    maxVal = val[i]
                    idx = i
                if val[i] == -2:
                    maxVal = -2
                    idx = i
                    break
            if maxVal == -2:
                self.attack(idx)
                self.returnKremlin()
                continue
            cache = self.vision
            if maxVal == 0:
                idx = randint(0, 2)
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
            if len(cache) != 1:
                self.takeItems(cache[1][idx])

    def takeItems(self, dic):
        if self.pos_x == 0 and self.pos_y == 0:
            return
        for (obj, value) in dic.items():
            if obj == "player":
                continue
            for _ in range(value):
                if obj != "food":
                    self.Take(obj)

    def getValue(self, dic):
        val = 0
        if dic.get("player"):
            if dic["player"] >= 6:
                print(f"Enemy base found: ({self.pos_x};{self.pos_y})")
                if not (-2 <= self.pos_x <= 2 and -2 <= self.pos_y <= 2):
                    return -2
            return -1
        for (key, value) in dic.items():
            if key != "food":
                val += value
        return val

    def attack(self, idx):
        if idx == 0:
            self.Left()
            self.Forward()
        if idx == 2:
            self.Right()
            self.Forward()
        self.Fork(Role.COMMANDO)

    def returnKremlin(self):
        super().returnKremlin()
        # refills and drop
        self.Inventory()
        while (self.Take("food") and self.inv["food"] <= EXPLORER_STASH):
            pass
        for (key, value) in self.inv.items():
            if key != "food":
                for _ in range(value):
                    self.Set(key)
        self.Forward()
        self.Forward()
