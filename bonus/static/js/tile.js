const ORIENTATIONS = { 1: 'Nord', 2: 'Est', 3: 'Sud', 4: 'Ouest' };
const RESOURCES = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'];
const parts = window.location.pathname.split('/');
const X = parseInt(parts[2]);
const Y = parseInt(parts[3]);

function make_player(id, p)
{
    const li = document.createElement('li');

    li.textContent = `#${id} — équipe ${p.team} — niveau ${p.level} — orientation ${ORIENTATIONS[p.orientation] || p.orientation}`;
    return li;
}

function render_players(players)
{
    const container = document.getElementById('players');
    const ul = document.createElement('ul');
    const p = document.createElement('p');

    container.innerHTML = '';
    if (!players.length) {
        p.textContent = 'Aucun joueur sur cette case.';
        container.append(p);
        return;
    }
    for (const [id, p] of players)
        ul.append(make_player(id, p));
    container.append(ul);
}

function render_resources(r)
{
    const container = document.getElementById('resources');
    const p = document.createElement('p');

    container.innerHTML = '';
    if (!r) {
        p.textContent = 'Aucune ressource connue sur cette case.';
        container.append(p);
        return;
    }
    p.textContent = RESOURCES.map((name, i) => `${name} ${r[i]}`).join(', ');
    container.append(p);
}

async function poll()
{
    let data;

    try {
        const reponse = await fetch('/state');
        if (!reponse.ok)
            throw new Error(`Fetch status : ${reponse.status}`);
        data = await reponse.json();
    } catch (erreur) {
        console.error(erreur.message);
        return;
    }
    if (!data.width)
        return;
    document.getElementById('title').textContent = `Case (${X}, ${Y})`;
    const players = Object.entries(data.players).filter(([, p]) => p.x === X && p.y === Y);
    render_players(players);
    render_resources(data.resources[`${X},${Y}`]);
}
setInterval(poll, 100);
poll();
