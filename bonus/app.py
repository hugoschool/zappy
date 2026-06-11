from flask import Flask, render_template, jsonify, request
from tcp_receiver import start_tcp_server
from log_buffer import buffer

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/logs')
def logs():
    since = int(request.args.get('since', 0))
    return jsonify({ 'logs': buffer.get_since(since), 'total': buffer.count() })

if __name__ == '__main__':
    start_tcp_server()
    app.run(use_reloader=False)
