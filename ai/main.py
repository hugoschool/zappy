from .Core import mainLoop
from argparse import ArgumentParser


def parsing():
    parsing = ArgumentParser(add_help=False)
    parsing.add_argument("-p", "--port", type=int, help="port number", required=True)
    parsing.add_argument("-n", "--name", type=str, help="Team name", required=True)
    parsing.add_argument("-h", "--host", type=str, help="Host name of the machine", default="127.0.0.1", required=False)
    parsing.add_argument('--help', action='help', help='show this help message and exit')
    return parsing.parse_args()

def main():
    args = parsing()
    mainLoop(args.host, args.port, args.name)


if __name__ == "__main__":
    main()
