from .AgenticIntelligenceKpiWorkflow import *
from .Communication import createSocket
from select import *
import socket as skt


def mainLoop(machine, port, name):
    firstConnection = Freakster((), createSocket(machine, port, name))
    family = {firstConnection.socket.fileno(): firstConnection}

    pollObject = poll()
    for freakyAi in family.values():
        pollObject.register(freakyAi.socket, POLLIN)

    while True:
        pollEvent = pollObject.poll(0)

        for socket, event in pollEvent:
            if (event & POLLIN):
                ai = family[socket]
                if ai.handshake == False and ai.welcome == False:
                    ai.firstHandshake(name)
                elif ai.handshake == False and ai.welcome == True:
                    if ai.finalHandshake() == True:
                        newAi = Freakster((), createSocket(machine, port, name))
                        family.update({newAi.socket.fileno: newAi})
                else:
                    s = ai.receive()
                    print(s)

        if (len(family) == 0):
            break;
        for freakyAi in family.values():
            freakyAi.doThing()

    print("End of the program.")
