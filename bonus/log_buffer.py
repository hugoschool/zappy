import threading
from typing import final
from dataclasses import dataclass

@dataclass
class DataPlayer:
    id: int
    x: int
    y: int
    orientation: int
    level: int
    team: str

@dataclass
class DataState:
    width: int
    height: int
    teams: list[str]
    players: dict[str, DataPlayer]

DataTile = list[DataPlayer]

@final
class GameState:
    def __init__(self) -> None:
        self._lock: threading.Lock = threading.Lock()
        self.width: int = 0
        self.height: int = 0
        self.teams: list[str] = []
        self.players: dict[str, DataPlayer] = {}

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
                self.players[pid] = DataPlayer(
                    id = int(pid),
                    x = int(parts[2]),
                    y = int(parts[3]),
                    orientation = int(parts[4]),
                    level = int(parts[5]),
                    team = parts[6],
                )
            elif cmd == "ppo" and len(parts) == 5:
                pid = parts[1].lstrip('#')
                if pid in self.players:
                    self.players[pid].x = int(parts[2])
                    self.players[pid].y = int(parts[3])
                    self.players[pid].orientation = int(parts[4])
            elif cmd == "pdi" and len(parts) == 2:
                pid = parts[1].lstrip('#')
                _ = self.players.pop(pid)

    def get_state(self) -> DataState:
        with self._lock:
            return DataState(
                width = self.width,
                height = self.height,
                teams = list(self.teams),
                players = dict(self.players),
            )

    def get_tile(self, x: int, y: int) -> DataTile:
        with self._lock:
            tile: list[DataPlayer] = []
            for player in self.players.values():
                if player.x == x and player.y == y:
                    tile.append(player)
            return tile

buffer = GameState()
