from .Communication import SocketReceiveError
from enum import Enum
import threading


class Role(Enum):
    LEADER = 0
    OLIGARCH = 1
    EXPLORER = 2
    FOOD_FACTORY = 3
    SACRIFICE = 4


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

    def __init__(self, socket, toAdd):
        # Player game info
        self.freakyId = Freakster.FreakyId
        self.pos_x = 0 if Freakster.FreakyId == 0 else -1
        self.pos_y = 0 if Freakster.FreakyId == 0 else -1
        self.inv = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0,
                    "mendiane": 0, "phiras": 0, "thystame": 0}
        self.direction = Direction.UP
        self.map_dim = (-1, -1)
        self.vision = []

        # Thread related
        self.received = None
        self.thread = None
        self.threadEvent = threading.Event()
        self.toAdd = toAdd

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
        self.threadEvent.clear()
        if (self.received.startswith("message")):
            self.handleBroadcast()
            self.waitThread()
        if (self.received == "Elevation Underway"):
            self.waitThread()
        if (self.received.startswith("Current level:")):
            self.level += 1
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
            return -1
        if len(arr) != 3:
            return -1
        self.map_dim = (arr[1], arr[2])
        self.handshake = True
        return arr[0]

    def receive(self):
        s = ""
        decode = ""
        rec = ""
        while not '\n' in decode:
            rec = self.socket.recv(4096)
            if rec == b'':
                self.received = ""
                raise SocketReceiveError("Server has stopped.")
            decode = rec.decode("ascii")
            s += decode
        s = s.strip("\n")
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
            if len(self.vision) <= 1:
                self.vision = []
            else:
                for i in range(1, len(self.vision)):
                    self.vision[1].pop()
                    self.vision[0] = self.vision[1].pop(0)
                self.vision.pop()

    def Right(self):
        self.send("Right")
        self.waitThread()
        if self.received == "ok":
            self.direction = Direction((self.direction.value + 1) % 4)
            if self.vision != []:
                self.vision = self.vision[0]


    def Left(self):
        self.send("Left")
        self.waitThread()
        if self.received == "ok":
            self.direction = Direction((self.direction.value - 1) % 4)
            if self.vision != []:
                self.vision = self.vision[0]

    def Look(self):
        self.send("Look")
        self.waitThread()
        if self.received != "":
            s = self.received.replace("[", "").replace("]", "")
            arr = s.split(",")
            length = 1
            to_add = []
            while arr != []:
                tmp = []
                for i in range(length):
                    if arr == []:
                        break;
                    if arr[0] == '' or arr[0] == ' ':
                        tmp.append({})
                    else:
                        d = {}
                        s = arr[0].strip().split(" ")
                        for i in s:
                            if d.get(i) != None:
                                d[i] = d[i] + 1
                            else:
                                d[i] = 1
                        tmp.append(d)
                    arr.pop(0)
                to_add.append(tmp)
                length += 2
            self.vision = to_add

    def Inventory(self):
        self.send("Inventory")
        self.waitThread()
        inventory = self.received.replace(",", " ").replace("[", " ").replace("]", " ").split()
        for i in range(0, len(inventory), 2):
            self.inv[inventory[i]] = int(inventory[i + 1])

    def Broadcast(self, text):
        self.send(f"Broadcast {text}")
        self.waitThread()
        if self.received == "ok":
            pass

    def ConnectNbr(self):
        self.send("Connect_nbr")
        self.waitThread()
        if self.received == "ok":
            pass

    def Fork(self, role: Role):
        self.send("Fork")
        self.waitThread()
        if self.received == "ok":
            self.toAdd.put(role)
            pass

    def Eject(self):
        self.send("Eject")
        self.waitThread()
        if self.received == "ok":
            pass

    def Take(self, obj):
        self.send(f"Take {obj}")
        self.waitThread()
        if self.received == "ok":
            self.inv[obj] += 1
            return True
        return False

    def Set(self, obj):
        if self.inv[obj] < 1:
            return
        self.send(f"Set {obj}")
        self.waitThread()
        if self.received == "ok":
            self.inv[obj] -= 1
            pass
        self.threadEvent.clear()

    def Incantation(self):
        self.send("Incantation")
        self.waitThread()

    def mainloop(self):  # method meant to be overriden
        while (True):
            self.Forward()
            self.Forward()
            self.Right()
