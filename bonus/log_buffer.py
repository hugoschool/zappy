import threading

class LogBuffer:
    def __init__(self):
        self._logs = []
        self._lock = threading.Lock()

    def append(self, log):
        with self._lock:
            self._logs.append(log)

    def get_since(self, index):
        with self._lock:
            return list(self._logs[index:])

    def count(self):
        with self._lock:
            return len(self._logs)

buffer = LogBuffer()
