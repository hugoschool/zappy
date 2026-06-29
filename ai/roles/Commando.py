from ..AgenticIntelligenceKpiWorkflow import Freakster, Role
import re


class Commando(Freakster):
    def mainloop(self):
        print("Commando created: Attack Protocol Initialized")
        self.findEnemies()
        while True:
            self.Forward()
            self.Eject()

    def findEnemies(self):
        while True:
            self.Look()
            if self.vision[1][1].get("player") and self.vision[1][1]["player"] >= 4:
                break
            self.Right()

    def Broadcast(self, text):
        self.send(f"Broadcast {text}")
        self.waitThread()
        if self.received != "ok":
            pass

    def handleBroadcast(self):
        message = re.match(r"message (\d), (.*)", self.received)
        message = message.group(2)
        self.Broadcast(message)
