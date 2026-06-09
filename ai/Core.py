from .Communication import createSocket, handshake
from .AgenticIntelligenceKpiWorkflow import *
from select import *


def initConnection(machine, port, name):
    socket = createSocket(machine, port, name)

    s = handshake(socket, name)
    if (s != ""):
        try:
            arr = [int(tmp) for tmp in s.split()]
        except ValueError:
            None
        if arr[0] > 0:
            return (True, Ai((arr[1], arr[2]), socket))
        return (False, Ai((arr[1], arr[2]), socket))


def mainLoop(machine, port, name):
    family = []

    ret = initConnection(machine, port, name)
    while (ret[0] == True):
        family.append(ret[1])
        ret = initConnection(machine, port, name)
    family.append(ret[1])

    pollObject = poll()

    for freakster in family:
        pollObject.register(freakster.socket, POLLIN)

    while True:
        pollEvent = pollObject.poll(0)

        for fd, event in pollEvent:
            print(f"{fd} {event}")

        if (len(family) == 0):
            break;
        for i in range(len(family)):
            family[i].doThing()

    print("End of the program.")
