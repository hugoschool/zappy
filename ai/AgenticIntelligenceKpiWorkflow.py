from .Communication import SocketReceiveError
from enum import Enum

class Direction(Enum):
    UNDEFINED = 0
    UP = 1
    RIGHT = 2
    DOWN = 3
    LEFT = 4

class Freakster:
    def __init__(self, x, y, socket):
        self.pos_x = x
        self.pos_y = y
        self.direction = Direction.UNDEFINED
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
        self.pos = (arr[1], arr[2])
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
        self.socket.send(str.encode("Forward" + "\n"))

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
        self.send("Forward")
        result = self.receive()
        if result == "ok":
            self.moveForward()

    def Right(self):
        self.send("Right")
        result = self.receive()
        if result == "ok":
            self.direction += 1 % 4