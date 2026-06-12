from .AgenticIntelligenceKpiWorkflow import Freakster, Status
from .Communication import createSocket, SocketReceiveError
from select import poll, POLLIN
import socket as skt
import threading


def createFreakster(family, pollObject, socket):
    global FreakyId
    newAi = Freakster(0, 0, socket)
    family.update({newAi.socket.fileno(): newAi})
    pollObject.register(newAi.socket, POLLIN)


def slimeFreakster(ai, socketfd, pollObject, family):
    del family[socketfd]
    pollObject.unregister(socketfd)
    ai.threadEvent.set()
    ai.thread.join()
    ai.socket.close()


def mainLoop(addr, port, name):
    pollObject = poll()
    family = {}
    createFreakster(family, pollObject, createSocket(addr, port, name))

    while True:
        pollEvent = pollObject.poll(0)

        for socketfd, event in pollEvent:
            if (event & POLLIN):
                ai = family[socketfd]
                if not ai.handshake and not ai.welcome:
                    try:
                        ai.firstHandshake(name)
                    except SocketReceiveError:
                        slimeFreakster(ai, socketfd, pollObject, family)
                elif not ai.handshake and ai.welcome:
                    try:
                        res = ai.finalHandshake()
                        if res:
                            createFreakster(family, pollObject, createSocket(addr, port, name))
                        ai.startThread()
                    except SocketReceiveError:
                        slimeFreakster(ai, socketfd, pollObject, family)
                else:
                    try:
                        s = ai.receive()
                        ai.threadEvent.set()
                    except SocketReceiveError:
                        slimeFreakster(ai, socketfd, pollObject, family)

        if len(family) == 0:
            break

    print("End of the program.")
