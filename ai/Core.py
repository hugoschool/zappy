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
        t = threading.Thread(target=freakyAi.MainLoopBum)
        threads.append(t)
    for t in threads:
        t.start()

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
                        print("final handshaked")
                        ai.threadEvent.set()
                        print(ai.threadEvent)
                        if res == True:
                            newAi = Freakster(0, 0, createSocket(machine, port, name))
                            family.update({newAi.socket.fileno: newAi})
                            pollObject.register(newAi.socket, POLLIN)
                    except SocketReceiveError:
                        slimeFreakster(ai, family, socketfd, pollObject)
                else:
                    try:
                        print("trying to receive type shit")
                        s = ai.receive()
                        # ai.received = s
                        print("received:", s)
                        ai.threadEvent.set()
                        # if ai.status == Status.WAITING and ai.receiveWaiting != None:
                            # ai.receiveWaiting(s)
                            # if ai.status != Status.AVAILABLE:
                                # ai.checkReceive(s)
                        # else:
                            # ai.checkReceive(s)
                    except SocketReceiveError:
                        slimeFreakster(ai, family, socketfd, pollObject)

        if len(family) == 0:
            break
        for i in family.values():
            if i.handshake == True:
                i.doThing()
    for t in threads:
        t.join()
    print("End of the program.")
