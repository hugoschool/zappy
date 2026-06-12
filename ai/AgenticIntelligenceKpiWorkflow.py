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
    FreakyId = 0

    def __init__(self, x, y, socket):
        # Player game info
        self.freakyId = Freakster.FreakyId
        self.pos_x = x                         # TODO: Just wrong :/
        self.pos_y = y
        self.inv = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0,
                    "mendiane": 0, "phiras": 0, "thystame": 0}
        self.direction = Direction.UP

        # Thread related
        self.received = None
        self.thread = None
        self.threadEvent = threading.Event()

        # Socket related
        self.socket = socket
        self.welcome = False
        self.handshake = False

        # Update values
        Freakster.FreakyId += 1
        self.threadEvent.clear()

    def startThread(self):
        t = threading.Thread(target=self.Loop)
        self.thread = t
        self.thread.start()

    def waitThread(self):
        self.threadEvent.wait()
        if (self.received == "brodcast"):
            self.handleBroadcast()
            self.waitThread()
        # faire la mm chose sur le eject et sur le dead?
        # TODO better handling of dead ?
        if (self.received == "" or self.received == "dead"):
            raise SocketReceiveError("Server has stopped, killing thread")

    def firstHandshake(self, name):
        """First step of the Handshake, receive WELCOME and send team name"""
        s = self.receive()
        if s == "WELCOME":
            self.send(name)
            self.welcome = True

    def finalHandshake(self):
        """Final step of the Handshake, receive nb_connection and dimmension of
        the map
        Return True if we can connect another AI, False otherwise"""
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
        if s == b'':
            self.received = ""
            raise SocketReceiveError("Server has stopped.")
        s = s.decode("ascii").strip("\n")
        self.received = s
        return s

    def send(self, s):
        self.socket.send(str.encode(s + "\n"))

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

    def Loop(self):
        try:
            while (True):
                self.mainloop()
        except SocketReceiveError:
            print("Thread terminate")
            return                   # thread terminate here

    # TODO: gérer la concurrence sur la variable self.received
    def Forward(self):
        self.send("Forward")
        self.waitThread()
        if (self.received == "ok"):
            self.moveForward()
        self.threadEvent.clear()

    def Right(self):
        self.send("Right")
        self.waitThread()
        if self.received == "ok":
            self.direction = Direction((self.direction.value + 1) % 4)
        self.threadEvent.clear()

    def Left(self):
        self.send("Left")
        self.waitThread()
        if self.received == "ok":
            self.direction = Direction((self.direction.value - 1) % 4)
        self.threadEvent.clear()

    def Look(self):
        self.send("Look")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def Inventory(self):
        self.send("Inventory")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def Broadcast(self, text):
        self.send(f"Broadcast {text}")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def ConnectNbr(self):
        self.send("Connect_nbr")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def Fork(self):
        self.send("Fork")
        self.waitThread()
        if self.received == "ok":
            # Renvoyer au Main Thread le fork pour connecter le nouveau client
            pass
        self.threadEvent.clear()

    def Eject(self):
        self.send("Eject")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def Take(self, obj):
        self.send(f"Take {obj}")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def Set(self, obj):
        if self.inv[obj] < 1:
            return
        self.send(f"Set {obj}")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def Incantation(self):
        self.send("Incantation")
        self.waitThread()
        if self.received == "ok":
            pass
        self.threadEvent.clear()

    def mainloop(self):  # method meant to be overriden
        self.Forward()
        self.Fork()
