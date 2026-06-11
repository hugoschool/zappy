from .Communication import SocketReceiveError
from enum import Enum
import threading


class Role(Enum):
    OLIGARCH = 0
    EXPLORER = 1
    FOOD_FACTORY = 2
    SACRIFICE = 3


class Direction(Enum):
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3


class Status(Enum):
    AVAILABLE = 0
    WAITING = 1


class Freakster:
    def __init__(self, x, y, socket):
        self.pos_x = x
        self.pos_y = y
        self.received = None
        self.threadEvent = threading.Event()
        self.threadEvent.clear()
        self.direction = Direction.UP
        self.inv = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0,
                    "mendiane": 0, "phiras": 0, "thystame": 0}
        self.socket = socket
        self.welcome = False
        self.handshake = False

    def firstHandshake(self, name):
        s = self.receive()
        if s == "WELCOME":
            self.send(name)
            self.welcome = True

    def finalHandshake(self):
        s = self.receive()
        try:
            arr = [int(tmp) for tmp in s.split()]
        except ValueError:
            return
        if len(arr) != 3:
            return
        self.pos_x = arr[1]
        self.pos_y = arr[2]
        self.handshake = True
        if arr[0] > 0:
            return True
        return False

    def receive(self):
        s = self.socket.recv(4096)
        print(s)
        if s == b'':
            raise SocketReceiveError("Server has stopped.")
        return s.decode("ascii").strip("\n")

    def send(self, s):
        self.socket.send(str.encode(s + "\n"))

    def doThing(self):
        self.Forward()
        # self.socket.send(str.encode("Forward" + "\n"))

    def moveForward(self):
        if self.direction == Direction.UP:
            self.pos_y += 1
        if self.direction == Direction.RIGHT:
            self.pos_x += 1
        if self.direction == Direction.DOWN:
            self.pos_y -= 1
        if self.direction == Direction.LEFT:
            self.pos_x -= 1


    def handleBroadcast(self, message):
        pass

    def handleEject(self, message):
        pass

    def checkReceive(self, receive):
        if (receive.split()[0] == "message"):
            self.handleBroadcast(receive)
            return False
        if (receive.split()[0] == "eject"):
            self.handleEject(receive)
            return False
        return True


    #TODO: gérer la concurrence sur la variable self.received
    def Forward(self):
        self.send("Forward")
        self.threadEvent.wait()
        print("Forwarded")
        if (self.received == "ok"):
            self.moveForward()
        self.threadEvent.clear()

    def MainLoopBum(self):
        while (True):
            self.Forward()
            self.Forward()
            self.Right()

    def Right(self):
        self.send("Right")
        self.threadEvent.wait()
        if self.received == "ok":
            self.direction = Direction((self.direction.value + 1) % 4)
        self.threadEvent.clear()

    def Left(self):
        self.send("Left")
        self.threadEvent.wait()
        if self.received == "ok":
            self.direction = Direction((self.direction.value - 1) % 4)
        self.threadEvent.clear()

    def Look(self):
        self.send("Look")
        # Wait Thread

    def Inventory(self):
        self.send("Inventory")
        # Wait Thread

    def Broadcast(self, text):
        self.send(f"Broadcast {text}")
        # Wait Thread

    def ConnectNbr(self):
        self.send("Connect_nbr")
        # Wait Thread

    def Fork(self):
        self.send("Fork")
        # Wait Thread

    def Eject(self):
        self.send("Eject")
        # Wait Thread

    def Take(self, obj):
        self.send(f"Take {obj}")
        # Wait Thread

    def Set(self, obj):
        if self.inv[obj] < 1:
            return
        self.send(f"Set {obj}")
        # Wait Thread

    def Incantation(self):
        self.send("Incantation")
        # Wait Thread
