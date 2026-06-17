async function poll()
{
    const data = await fetch('/state').then(r => r.json());
    const cells = {};
    let html = '';

    if (!data.width)
        return;
    document.getElementById('info').textContent =
        `${data.width}x${data.height} | teams: ${data.teams.join(', ')} | players: ${Object.keys(data.players).length}`;
    for (const [id, p] of Object.entries(data.players))
        cells[`${p.x},${p.y}`] = (cells[`${p.x},${p.y}`] || '') + `#${id}`;
    for (let y = 0; y < data.height; y++) {
        html += '<tr>';
        for (let x = 0; x < data.width; x++) {
            const p = cells[`${x},${y}`];
            html += `<td colspan="2" class="${p ? 'player' : ''}"><a href="/tile/${x}/${y}">${p || ''}</a></td>`;
        }
        html += '</tr>';
    }
    document.getElementById('map').innerHTML = html;
}
setInterval(poll, 1000);
poll();
