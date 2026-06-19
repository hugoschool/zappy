from ..AgenticIntelligenceKpiWorkflow import Freakster


class Explorer(Freakster):
    objective = {"linemate": 9, "deraumere": 8, "sibur": 10,
                 "mendiane": 5, "phiras": 6, "thystame": 1}
    treshold = {}

    def mainloop(self):
        self.Look()
        while self.vision == []:
            self.Forward()
            self.look()
        # si il y a du thystame faire des tour du monde sinon glouton
        if not self.vision[0][0].get("thystame"):
            self.gloutonTypeShit()
        self.worldTour()

    def gloutonTypeShit(self):
        while True:
            idx = 1
            maxVal = 0
            val = []
            if len(self.vision) < 2:
                self.Look()
            for i in self.vision[1]:
                val.append(getValue(i))
            for i in range(len(val)):
                if val[i] > maxVal:
                    maxVal = val[i]
                    idx = i
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

    def worldTour(self):
        a = 0

    def takeItems(self, dic):
        for (obj, value) in dic.items():
            if obj == "player":
                continue
            for i in range(value):
                self.Take(obj)
                if obj != "food":
                    self.objective[obj] = self.objective[obj] - 1


def getValue(dic):
    val = 0
    if dic.get("player"):
        return -1
    for (key, value) in dic.items():
        if key != "food":
            val += value
    return val
