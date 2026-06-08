import socket


class Client:
    def __init__(self, ip, port, socket):
        self.ip = ip
        self.port = port
        self.socket = socket
