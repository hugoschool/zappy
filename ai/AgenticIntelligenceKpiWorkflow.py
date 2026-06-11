from .Communication import SocketReceiveError
from enum import Enum

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
        self.direction = Direction.UP
        self.socket = socket
        self.status = Status.AVAILABLE
        self.receiveWaiting = None
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

    def Forward(self):
        # print("caca")
        self.send("Forward")
        self.status = Status.WAITING
        self.receiveWaiting = self.ExecuteForward

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

    def ExecuteForward(self, receive):
        if (receive == "ok"):
            self.moveForward()
            self.status = Status.AVAILABLE
            print("forwarded")


    def Right(self):
        self.send("Right")
        result = self.receive()
        if result == "ok":
            self.direction = (self.direction + 1) % 4
