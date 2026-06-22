import cmd_buffer
from data_class import DataEgg, DataPlayer

class GuiCmd:
    def cmd_msz(self, state: cmd_buffer.GameState):
        state.width = int(state.parts[1])
        state.height = int(state.parts[2])

    def cmd_tna(self, state: cmd_buffer.GameState):
        state.teams.append(state.parts[1])

    def cmd_pnw(self, state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        state.players[pid] = DataPlayer(
            id = int(pid),
            x = int(state.parts[2]),
            y = int(state.parts[3]),
            orientation = int(state.parts[4]),
            level = int(state.parts[5]),
            team = state.parts[6],
        )

    def cmd_ppo(self, state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        if pid in state.players:
            state.players[pid].x = int(state.parts[2])
            state.players[pid].y = int(state.parts[3])
            state.players[pid].orientation = int(state.parts[4])

    def cmd_pdi(self, state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        _ = state.players.pop(pid)

    def cmd_bct(self, state: cmd_buffer.GameState):
        x = int(state.parts[1])
        y = int(state.parts[2])
        state.resources[(x, y)] = [int(q) for q in state.parts[3:10]]

    def cmd_enw(self, state: cmd_buffer.GameState):
        eid = state.parts[1].lstrip('#')
        pid = state.parts[2].lstrip('#')
        state.eggs[eid] = DataEgg(
            id = int(eid),
            player_id = int(pid),
            x = int(state.parts[3]),
            y = int(state.parts[4]),
        )

    def cmd_pdr(self, state: cmd_buffer.GameState):
        pid = state.parts[1].lstrip('#')
        i = int(state.parts[2])
        if pid in state.players:
            p = state.players[pid]
            if (p.x, p.y) in state.resources:
                state.resources[(p.x, p.y)][i] += 1
