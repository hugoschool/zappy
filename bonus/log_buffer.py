import threading
from typing import final
from data_class import DataTile, DataEgg, DataPlayer, DataState

@final
class GameState:
    def __init__(self) -> None:
        self._lock: threading.Lock = threading.Lock()
        self.width: int = 0
        self.height: int = 0
        self.teams: list[str] = []
        self.players: dict[str, DataPlayer] = {}
        self.eggs: dict[str, DataEgg] = {}
        self.resources: dict[tuple[int, int], list[int]] = {}

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
            elif cmd == "bct" and len(parts) == 10:
                x = int(parts[1])
                y = int(parts[2])
                self.resources[(x, y)] = [int(q) for q in parts[3:10]]
            elif cmd == "enw" and len(parts) == 5:
                eid = parts[1].lstrip('#')
                pid = parts[2].lstrip('#')
                self.eggs[eid] = DataEgg(
                    id = int(eid),
                    player_id = int(pid),
                    x = int(parts[3]),
                    y = int(parts[4]),
                )
            elif cmd == "pdr" and len(parts) == 3:
                pid = parts[1].lstrip('#')
                i = int(parts[2])
                if pid in self.players:
                    p = self.players[pid]
                    if (p.x, p.y) in self.resources:
                        self.resources[(p.x, p.y)][i] += 1

    def get_state(self) -> DataState:
        with self._lock:
            return DataState(
                width = self.width,
                height = self.height,
                teams = list(self.teams),
                players = dict(self.players),
                eggs = dict(self.eggs),
                resources = dict(self.resources),
            )

    def get_tile(self, x: int, y: int) -> DataTile:
        with self._lock:
            tile: list[DataPlayer] = []
            for player in self.players.values():
                if player.x == x and player.y == y:
                    tile.append(player)
            return tile

buffer = GameState()
