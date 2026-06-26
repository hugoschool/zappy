from .Communication import SocketReceiveError
from itertools import cycle
from enum import Enum
import base64
import threading
import re


OLIGARCH_STASH = 20
CALL_MESSAGE = "hop on diddyboy 🥭"


class Role(Enum):
    LEADER = 0
    OLIGARCH = 1
    EXPLORER = 2
    STRANDED = 3
    FOOD_FACTORY = 4
    SACRIFICE = 5
    SPETSNAZ = 6
    COMMANDO = 7


class Direction(Enum):
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3


class Status(Enum):
    AVAILABLE = 0
    WAITING = 1


class Freakster:
    def __init__(self, socket, toAdd):
        # Player game info
        self.level = 1
        self.pos_x = 0
        self.pos_y = 0
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
        self.queue = []

        # Update values
        self.threadEvent.clear()

    def startThread(self):
        t = threading.Thread(target=self.Loop)
        self.thread = t
        self.thread.start()

    def waitThread(self):
        if len(self.queue) > 0:
            self.receive()
            self.threadEvent.set()
        self.threadEvent.wait()
        self.threadEvent.clear()
        if (self.received.startswith("message")):
            self.handleBroadcast()
            self.waitThread()
        if (self.received == "Elevation underway"):
            self.waitThread()
        if (self.received.startswith("Current level:")):
            self.level += 1
            self.waitThread()
        # faire la mm chose sur le eject et sur le dead?
        if (self.received.startswith("eject")):
            self.handleEject()
            self.waitThread()
        if (self.received == "" or self.received == "dead"):
            raise SocketReceiveError("Server has stopped, killing thread")

    def firstHandshake(self, name):
        """First step of the Handshake, receive WELCOME and send team name"""
        s = self.receive()
        if s == "WELCOME":
            self.send(name)
            self.name = name
            self.welcome = True

    def finalHandshake(self):
        """Final step of the Handshake, receive nb_connection and dimension of
        the map
        Return nb >= 0 if connection success, -1 otherwise"""
        try:
            nb = self.receive()
            dim = self.receive()
        except SocketReceiveError:
            return -1
        try:
            nb = int(nb)
            arr = [int(tmp) for tmp in dim.split()]
        except ValueError:
            return -1
        self.map_dim = (arr[0], arr[1])
        self.handshake = True
        return nb

    def receive(self):
        if len(self.queue) != 0:
            val = self.queue.pop(0)
            self.received = val
            return val
        s = b''
        decode = ""
        rec = ""
        while b'\n' not in s:
            try:
                rec = self.socket.recv(4096)
                if rec == b'':
                    self.received = ""
                    raise SocketReceiveError("Server has stopped.")
                s += rec
            except ConnectionResetError:
                print("\nConnection Reset by Peer error\n")
                raise SocketReceiveError("Server has stopped.")
        s = s.decode("ascii")
        self.queue = s.splitlines()
        ret = self.queue.pop(0)
        self.received = ret
        return ret

    def send(self, s):
        try:
            self.socket.send(str.encode(s + "\n"))
        except BrokenPipeError:
            raise SocketReceiveError("Server has stopped.")

    def moveForward(self):
        if self.direction == Direction.UP:
            self.pos_y += 1
        if self.direction == Direction.RIGHT:
            self.pos_x += 1
        if self.direction == Direction.DOWN:
            self.pos_y -= 1
        if self.direction == Direction.LEFT:
            self.pos_x -= 1

        if self.pos_x > (self.map_dim[0] / 2):
            self.pos_x = -self.pos_x + 2
        if self.pos_x < -(self.map_dim[0] / 2):
            self.pos_x = -self.pos_x - 2
        if self.pos_y > (self.map_dim[1] / 2):
            self.pos_y = -self.pos_y + 2
        if self.pos_y < -(self.map_dim[1] / 2):
            self.pos_y = -self.pos_y - 2

    def handleBroadcast(self):
        message = re.match(r"message (\d), (.*)", self.received)
        tile = int(message.group(1))
        message = message.group(2)
        try:
            message = base64.b64decode(message).decode()
        except Exception:
            return None
        message = self.xor(message, self.name)
        return (tile, message)


    def Broadcast(self, text):
        encoded = self.xor(text, self.name)
        encoded = bytes(encoded, "utf-8")
        encoded = base64.b64encode(encoded).decode()
        self.send(f"Broadcast \"{encoded}\"")
        self.waitThread()
        if self.received != "ok":
            pass


    def handleEject(self):
        pass

    def Loop(self):
        try:
            self.mainloop()
        except SocketReceiveError:
            return                   # thread terminate here

    def Forward(self):
        self.send("Forward")
        self.waitThread()
        if (self.received == "ok"):
            self.moveForward()
            if len(self.vision) <= 1:
                self.vision = []
            else:
                for i in range(1, len(self.vision)):
                    self.vision[i].pop()
                    self.vision[i].pop(0)
                    self.vision[i - 1] = self.vision[i]
                self.vision.pop()

    def Right(self):
        self.send("Right")
        self.waitThread()
        if self.received == "ok":
            self.direction = Direction((self.direction.value + 1) % 4)
            if self.vision != []:
                self.vision = [self.vision[0]]

    def Left(self):
        self.send("Left")
        self.waitThread()
        if self.received == "ok":
            self.direction = Direction((self.direction.value - 1) % 4)
            if self.vision != []:
                self.vision = [self.vision[0]]

    def Look(self):
        self.send("Look")
        self.waitThread()
        try:
            s = self.received.replace("[", "").replace("]", "")
            arr = s.split(",")
            length = 1
            new_vision = []
            while arr != []:
                case_content = []
                for i in range(length):
                    if arr[0] == '' or arr[0] == ' ':
                        case_content.append({})
                    else:
                        case_content.append(fill_case(arr[0].strip().split(" ")))
                    arr.pop(0)
                new_vision.append(case_content)
                length += 2
            self.vision = new_vision
        except Exception:
            self.Look()

    def Inventory(self):
        self.send("Inventory")
        self.waitThread()
        inventory = self.received.replace(",", " ").replace("[", " ").replace("]", " ").split()
        try:
            for i in range(0, len(inventory), 2):
                self.inv[inventory[i]] = int(inventory[i + 1])
        except Exception:
            self.Inventory()

    def ConnectNbr(self):
        self.send("Connect_nbr")
        self.waitThread()
        nb = 0
        try:
            nb = int(self.received)
        except Exception:
            pass
        return nb

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
        if obj not in self.inv or self.inv[obj] < 1:
            return
        self.send(f"Set {obj}")
        self.waitThread()
        if self.received == "ok":
            self.inv[obj] -= 1
            pass

    def Incantation(self):
        self.send("Incantation")

    def mainloop(self):  # method meant to be overriden
        while (True):
            self.Forward()
            self.Forward()
            self.Right()

    def xor(self, message, key):
        return ''.join(chr(ord(c)^ord(k)) for c,k in zip(message, cycle(key)))

def fill_case(s):
    d = {}
    for i in s:
        if d.get(i) != None:
            d[i] = d[i] + 1
        else:
            d[i] = 1
    return d
