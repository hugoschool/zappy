from ..AgenticIntelligenceKpiWorkflow import Freakster, Role
import re


class Perroquet(Freakster):
    def __init__(self, socket, toAdd):
        super().__init__(socket, toAdd)
        self.messagequeue = []

    def Broadcast(self, text):
        self.send(f"Broadcast {text}")
        self.waitThread()
        if self.received != "ok":
            pass

    def handleBroadcast(self):
        message = re.match(r"message (\d), (.*)", self.received)
        message = message.group(2)
        if message in self.messagequeue:
            return
        self.messagequeue.append(message)
        self.Broadcast(message)
