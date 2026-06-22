import socket
import threading
import time
from cmd_buffer import buffer
from typing import NoReturn

def start_tcp_server(host: str = "localhost", port: int = 4242):
    def _run() -> NoReturn:
        while True:
            try:
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as srv:
                    srv.connect((host, port))
                    srv.sendall(b"GRAPHIC\n")
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
            except (ConnectionRefusedError, OSError):
                time.sleep(2)
    threading.Thread(target=_run, daemon=True).start()
