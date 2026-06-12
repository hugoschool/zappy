import threading

class GameState:
    def __init__(self) -> None:
        self._lock = threading.Lock()
        self.width = 0
        self.height = 0
        self.teams: list[str] = []
        self.players: dict[str, int | list[str]] = {}

    def parse(self, line: str) -> None:
        with self._lock:
            parts = line.split()
            if not parts:
                return
            cmd = parts[0]
            if cmd == "msz" and len(parts) == 3:
                self.width = int(parts[1])
                self.height = int(parts[2])
            elif cmd == "tna" and len(parts) == 2:
                self.teams.append(parts[1])
            elif cmd == "pnw" and len(parts) == 7:
                pid = parts[1].lstrip('#')
                self.players[pid] = {
                    "x": int(parts[2]),
                    "y": int(parts[3]),
                    "orientation": int(parts[4]),
                    "level": int(parts[5]),
                    "team": parts[6],
                }

    def get_state(self) -> dict[str,int|list[str]|dict[str, int | list[str]]]:
        with self._lock:
            return {
                "width": self.width,
                "height": self.height,
                "teams": list(self.teams),
                "players": dict(self.players),
            }

buffer = GameState()
