from .client import Client
from os import fork
import socket as skt

def mainLoop(machine, port, name):
    mainSocket = skt.socket(skt.AF_INET, skt.SOCK_STREAM)
    mainSocket.setsockopt(skt.SOL_SOCKET, skt.SO_REUSEADDR, 1)
    try:
        mainSocket.connect((machine, port))
    except ConnectionRefusedError:
        print("The Client cannot connect to the server. It's either due to a wrong ip, a wrong port, or the server being closed.")
        exit(84)

    while True:
        s = mainSocket.recv(4096)
        if s == b'':
            print("Server has stopped. Exiting Program")
            exit(0)

        s = s.decode("UTF-8").strip('\n')
        if (s == "WELCOME"):
            id = fork()
            if id == 0:
                break
            else:
                # mainSocket.send(f"{name}\n".encode())
                print("I'm the Parent.")
        print(s)

    print("I'm the child.")
