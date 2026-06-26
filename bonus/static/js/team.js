const ORIENTATIONS = { 1: 'Nord', 2: 'Est', 3: 'Sud', 4: 'Ouest' };

function make_player(id, p)
{
    const li = document.createElement('li');

    li.textContent = `#${id} — niveau ${p.level} — position (${p.x}, ${p.y}) — orientation ${ORIENTATIONS[p.orientation] || p.orientation}`;
    return li;
}

function make_team(team, players)
{
    const h3 = document.createElement('h3');
    const ul = document.createElement('ul');
    const section = document.createElement('div');

    h3.textContent = `${team} — ${players.length} joueur(s)`;
    for (const [id, p] of players)
        ul.append(make_player(id, p));
    section.append(h3, ul);
    return section;
}

async function poll()
{
    let data;
    const teams = {};
    const container = document.getElementById('teams');

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
    for (const [id, p] of Object.entries(data.players))
        (teams[p.team] = teams[p.team] || []).push([id, p]);
    container.innerHTML = '';
    for (const [team, players] of Object.entries(teams))
        container.append(make_team(team, players));
}

setInterval(poll, 100);
poll();
