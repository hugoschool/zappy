import cmd_buffer
from data_class import DataEgg, DataPlayer

class CommandInterpretor:
    @staticmethod
    def msz(state: cmd_buffer.GameState):
        state.width = int(state.parts[1])
        state.height = int(state.parts[2])

    @staticmethod
    def tna(state: cmd_buffer.GameState):
        state.teams.append(state.parts[1])

    @staticmethod
    def pnw(state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        state.players[pid] = DataPlayer(
            id = int(pid),
            x = int(state.parts[2]),
            y = int(state.parts[3]),
            orientation = int(state.parts[4]),
            level = int(state.parts[5]),
            team = state.parts[6],
        )

    @staticmethod
    def ppo(state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        if pid in state.players:
            state.players[pid].x = int(state.parts[2])
            state.players[pid].y = int(state.parts[3])
            state.players[pid].orientation = int(state.parts[4])

    @staticmethod
    def pdi(state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        _ = state.players.pop(pid)

    @staticmethod
    def bct(state: cmd_buffer.GameState):
        x = int(state.parts[1])
        y = int(state.parts[2])
        state.resources[(x, y)] = [int(q) for q in state.parts[3:10]]

    @staticmethod
    def enw(state: cmd_buffer.GameState):
        eid = state.parts[1].lstrip('#')
        pid = state.parts[2].lstrip('#')
        state.eggs[eid] = DataEgg(
            id = int(eid),
            player_id = int(pid),
            x = int(state.parts[3]),
            y = int(state.parts[4]),
        )

    @staticmethod
    def pdr(state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        i = int(state.parts[2])
        if pid in state.players:
            p = state.players[pid]
            if (p.x, p.y) in state.resources:
                state.resources[(p.x, p.y)][i] += 1

    @staticmethod
    def plv(state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        if pid in state.players:
            state.players[pid].level = int(state.parts[2])
