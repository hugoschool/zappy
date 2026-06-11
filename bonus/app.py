from flask import Flask, render_template, jsonify, Response
from tcp_receiver import start_tcp_server

app = Flask(__name__)

@app.route('/')
def index() -> str:
    return render_template('index.html')

@app.route('/state')
def state() -> Response:
    from log_buffer import buffer
    return jsonify(buffer.snapshot())

if __name__ == '__main__':
    start_tcp_server()
    app.run(use_reloader=False)
