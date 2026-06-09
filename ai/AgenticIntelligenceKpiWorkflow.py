class Ai:
    def __init__(self, pos, socket):
        self.pos = pos
        self.socket = socket
        return

    def doThing(self):
        self.socket.send(str.encode("Forward" + "\n"))
        s = self.socket.recv(4096)
        if s == b'':
            print("Server has stopped.")
            self.socket.close()
            self.socket = None
