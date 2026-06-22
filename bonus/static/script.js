const RESOURCES = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'];
const RES_ROWS = [[0], [1, 2, 3], [4, 5, 6]];

function make_table(r, has_player)
{
    const table = document.createElement('table');

    table.className = "map";

    for (const row of RES_ROWS) {
        const tr = document.createElement('tr');
        for (const i of row) {
            const td = document.createElement('td');
            if (r && r[i])
                td.className += "item " + RESOURCES[i];
            else if (has_player)
                td.className += "playerl"
            else
                td.className = "default";
            tr.append(td);
        }
        table.append(tr);
    }
    return table;
}

function make_cell(x, y, player_text, r)
{
    const td = document.createElement('td');
    const a = document.createElement('a');

    if (player_text)
        td.className = 'player';
    a.href = `/tile/${x}/${y}`;
    a.textContent = player_text || '';
    td.append(a);
    td.append(make_table(r, player_text));
    return td;
}

async function poll()
{
    let data;
    const cells = {};

    try {
        const reponse = await fetch('/state');
        if (!reponse.ok) {
            throw new Error(`Fetch status : ${reponse.status}`);
        }
        data = await reponse.json();
    } catch (erreur) {
        console.error(erreur.message);
        return
    }
    if (!data.width)
        return;
    document.getElementById('info').textContent =
        `${data.width}x${data.height} | teams: ${data.teams.join(', ')} | players: ${Object.keys(data.players).length}`;
    for (const [id, p] of Object.entries(data.players))
        cells[`${p.x},${p.y}`] = (cells[`${p.x},${p.y}`] || '') + `#${id}`;
    const map = document.getElementById('map');
    map.innerHTML = '';
    for (let y = 0; y < data.height; y++) {
        const tr = document.createElement('tr');
        for (let x = 0; x < data.width; x++)
            tr.append(make_cell(x, y, cells[`${x},${y}`], data.resources[`${x},${y}`]));
        map.append(tr);
    }
}
setInterval(poll, 1000);
poll();
