import threading
from typing import final, cast
from collections.abc import Callable
from data_class import DataTile, DataEgg, DataPlayer, DataState
from CommandInterpretor import CommandInterpretor

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
        self.parts: list[str]
        self.cmds: dict[str, dict[str, Callable[[GameState],None]|int]] = {
            "msz": {
                "function": CommandInterpretor.msz,
                "arguments": 3
            },
            "tna": {
                "function": CommandInterpretor.tna,
                "arguments": 2
            },
            "pnw": {
                "function": CommandInterpretor.pnw,
                "arguments": 7
            },
            "ppo": {
                "function": CommandInterpretor.ppo,
                "arguments": 5
            },
            "pdi": {
                "function": CommandInterpretor.pdi,
                "arguments": 2
            },
            "bct": {
                "function": CommandInterpretor.bct,
                "arguments": 10
            },
            "enw": {
                "function": CommandInterpretor.enw,
                "arguments": 5
            },
            "pdr": {
                "function": CommandInterpretor.pdr,
                "arguments": 3
            },
            "plv": {
                "function": CommandInterpretor.plv,
                "arguments": 3
            }
        }

    def parse(self, line: str) -> None:
        with self._lock:
            self.parts = line.split()
            cmd = self.parts[0]
            if cmd in self.cmds and self.cmds[cmd]["arguments"] == len(self.parts):
                if not self.parts:
                    return
                cast(Callable[[GameState],None], self.cmds[cmd]["function"])(self)

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
