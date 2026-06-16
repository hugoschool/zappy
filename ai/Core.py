from .AgenticIntelligenceKpiWorkflow import Freakster, Role
from .roles import Oligarch
from .roles import FoodFactory
from .roles import Sacrifice
from .roles import Explorer
from .Communication import createSocket, SocketReceiveError
from select import poll, POLLIN
import socket as skt
from queue import Queue
import threading


def createFreakster(family, pollObject, socket, toAdd, role: Role):
    newAI: Freakster
    match role:
        case Role.OLIGARCH:
            newAI = Oligarch.Oligarch(socket, toAdd)
        case Role.EXPLORER:
            newAI = Explorer.Explorer(socket, toAdd)
        case Role.FOOD_FACTORY:
            newAI = FoodFactory.FoodFactory(socket, toAdd)
        case Role.SACRIFICE:
            newAI = Sacrifice.Sacrifice(socket, toAdd)
        case _:
            newAI = Freakster(socket, toAdd)
    family.update({newAI.socket.fileno(): newAI})
    pollObject.register(newAI.socket, POLLIN)

def slimeFreakster(ai, socketfd, pollObject, family):
    del family[socketfd]
    pollObject.unregister(socketfd)
    ai.threadEvent.set()
    ai.thread.join()
    ai.socket.close()


def mainLoop(addr, port, name):
    pollObject = poll()
    family = {}
    toAdd = Queue()
    socket = createSocket(addr, port, name)
    createFreakster(family, pollObject, socket, toAdd, Role.EXPLORER)
    ai = family[socket.fileno()]
    while (not ai.welcome):
        pollEvent = pollObject.poll(0)
        if (len(pollEvent) > 0 and pollEvent[0][1] & POLLIN):
            ai = family[pollEvent[0][0]]
            ai.firstHandshake(name)
            nbLeft = ai.finalHandshake()
            if nbLeft == -1:
                pollObject.unregister(socket.fileno())
                ai.socket.close()
                print("Could not connect client to server - aborting")
                return 84
            for i in range(nbLeft):
                createFreakster(family, pollObject, createSocket(addr, port, name), toAdd, Role.FOOD_FACTORY)
    ai.startThread()
    while True:
        if (toAdd.qsize() > 0):
            role = toAdd.get()
            createFreakster(family, pollObject, createSocket(addr, port, name), toAdd, role)
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
                        ai.finalHandshake()
                        ai.startThread()
                    except SocketReceiveError:
                        slimeFreakster(ai, socketfd, pollObject, family)
                else:
                    try:
                        ai.receive()
                        ai.threadEvent.set()
                    except SocketReceiveError:
                        slimeFreakster(ai, socketfd, pollObject, family)

        if len(family) == 0:
            break

    print("End of the program.")
