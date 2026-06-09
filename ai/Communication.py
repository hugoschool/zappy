from os import fork
import socket as skt


def createSocket(machine, port, name):
    s = skt.socket(skt.AF_INET, skt.SOCK_STREAM)
    s.setsockopt(skt.SOL_SOCKET, skt.SO_REUSEADDR, 1)
    try:
        s.connect((machine, port))
    except ConnectionRefusedError:
        print("The Client cannot connect to the server. It's either due to a wrong ip, a wrong port, or the server being closed.")
        exit(84)
    return s


def handshake(socket, name):
    s = socket.recv(4096)
    if s == b'':
        print("Server has stopped. Exiting Program")
        socket.close()
        return ""

    s = s.decode("ascii").strip('\n')
    if (s == "WELCOME"):
        socket.send(str.encode(name + "\n"))
        s = socket.recv(4096).decode("ascii").strip('\n')
        if (s == 'ko'):
            return ""
        else:
            return s
    return ""
