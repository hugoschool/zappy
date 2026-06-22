from flask import Flask, render_template, jsonify, Response
from dataclasses import asdict
from tcp_receiver import start_tcp_receiver
from cmd_buffer import buffer
from argparse import ArgumentParser

app = Flask(__name__)

@app.route('/')
def index() -> str:
    return render_template('index.html')

@app.route('/state')
def state() -> Response:
    state = buffer.get_state()
    data = asdict(state)
    data["resources"] = {f"{x},{y}": q for (x, y), q in state.resources.items()}
    return jsonify(data)

@app.route('/tile/<int:x>/<int:y>')
def tile(x: int, y: int) -> str:
    return render_template(
        'tile.html',
        x = x, y = y,
        players = buffer.get_tile(x, y),
        resources = buffer.resources.get((x, y)),
    )

if __name__ == '__main__':
    args = ArgumentParser(add_help=False)
    _ = args.add_argument("-h", "--host", type=str, help="Host name of the machine", default="127.0.0.1", required=False)
    _ = args.add_argument("-p", "--port", type=int, help="port number", default="4242", required=False)
    _ = args.add_argument("--help", action="help", help="show this help message and exit")
    args = args.parse_args()

    start_tcp_receiver(args.host, args.port) # pyright: ignore[reportAny]
    app.run(use_reloader=False)
