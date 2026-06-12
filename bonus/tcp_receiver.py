import socket
import threading
from log_buffer import buffer
from typing import NoReturn

def handle_client(conn: socket.socket) -> None:
    with conn:
        data = ""
        while True:
            chunk = conn.recv(4096).decode("utf-8", errors="replace")
            if not chunk:
                break
            data += chunk
            while "\n" in data:
                line, data = data.split("\n", 1)
                line = line.strip()
                if line:
                    buffer.parse(line)

def start_tcp_server(host="0.0.0.0", port=4343):
    def _run() -> NoReturn:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as srv:
            srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            srv.bind((host, port))
            srv.listen(5)
            while True:
                conn, _ = srv.accept()
                threading.Thread(target=handle_client, args=(conn,), daemon=True).start()
    threading.Thread(target=_run, daemon=True).start()
