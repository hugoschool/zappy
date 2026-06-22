import socket
import threading
import time
from cmd_buffer import buffer
from typing import NoReturn

def retrieve_data(srv: socket.socket):
    data = ""
    while True:
        chunk = srv.recv(4096).decode("utf-8", errors="replace")
        if not chunk:
            break
        data += chunk
        while "\n" in data:
            line, data = data.split("\n", 1)
            line = line.strip()
            if line:
                buffer.parse(line)

def start_tcp_receiver(host: str, port: int):
    def _run() -> NoReturn:
        while True:
            try:
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as srv:
                    srv.connect((host, port))
                    srv.sendall(b"GRAPHIC\n")
                    retrieve_data(srv)
            except (ConnectionRefusedError, OSError):
                time.sleep(2)
    threading.Thread(target=_run, daemon=True).start()
