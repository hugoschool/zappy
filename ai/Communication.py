from os import fork
import socket as skt


class SocketReceiveError(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__(self.message)

    def __str__(self):
        return f"SocketReceiveError: {self.message}"


def createSocket(machine, port, name):
    s = skt.socket(skt.AF_INET, skt.SOCK_STREAM)
    s.setsockopt(skt.SOL_SOCKET, skt.SO_REUSEADDR, 1)
    try:
        s.connect((machine, port))
    except ConnectionRefusedError:
        print("The Client cannot connect to the server. It's either due to a wrong ip, a wrong port, or the server being closed.")
        exit(84)
    return s
