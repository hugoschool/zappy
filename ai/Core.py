from .AgenticIntelligenceKpiWorkflow import Freakster, Status
from .Communication import createSocket, SocketReceiveError
from select import poll, POLLIN
import socket as skt
import threading


def slimeFreakster(ai, family, socketfd, pollObject):
    ai.socket.close()
    del family[socketfd]
    pollObject.unregister(socketfd)


def mainLoop(machine, port, name):
    firstConnection = Freakster(0, 0, createSocket(machine, port, name))
    family = {firstConnection.socket.fileno(): firstConnection}
    threads = []
    pollObject = poll()
    for freakyAi in family.values():
        pollObject.register(freakyAi.socket, POLLIN)

    while True:
        pollEvent = pollObject.poll(0)

        for socketfd, event in pollEvent:
            if (event & POLLIN):
                ai = family[socketfd]
                if ai.handshake == False and ai.welcome == False:
                    try:
                        ai.firstHandshake(name)
                    except SocketReceiveError:
                        slimeFreakster(ai, family, socketfd, pollObject)
                elif ai.handshake == False and ai.welcome == True:
                    try:
                        res = ai.finalHandshake()
                        # if res == True:
                        #     newAi = Freakster(0, 0, createSocket(machine, port, name))
                        #     family.update({newAi.socket.fileno: newAi})
                        #     pollObject.register(newAi.socket, POLLIN)
                        t = threading.Thread(target=ai.MainLoopBum)
                        threads.append(t)
                        t.start()
                    except SocketReceiveError:
                        slimeFreakster(ai, family, socketfd, pollObject)
                else:
                    try:
                        s = ai.receive()
                        ai.received = s
                        ai.threadEvent.set()
                    except SocketReceiveError:
                        slimeFreakster(ai, family, socketfd, pollObject)

        if len(family) == 0:
            break
        # for i in family.values():
        #     if i.handshake == True:
        #         i.doThing()
    for t in threads:
        t.join()
    print("End of the program.")
