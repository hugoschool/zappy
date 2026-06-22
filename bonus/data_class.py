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
class DataEgg:
    id: int
    player_id: int
    x: int
    y: int

@dataclass
class DataState:
    width: int
    height: int
    teams: list[str]
    players: dict[str, DataPlayer]
    eggs: dict[str, DataEgg]
    resources: dict[tuple[int, int], list[int]]

DataTile = list[DataPlayer]
