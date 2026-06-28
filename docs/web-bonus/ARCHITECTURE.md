# Architecture & Schema

This is the representation of the data flow between the Zappy Server & the Zappy Web Server.

## Zappy Web Server

The Zappy Web Server is made of:
- a TCP client using UNIX sockets
- Flask server

## Schema for the main page

```mermaid
stateDiagram-v2
    zappy_server --> zappy_web_server : Sending commands
    zappy_web_server --> zappy_server : Getting commands

    zappy_web_front --> zappy_web_server : Continously polling for the game state
```

## Schema for the tile page

```mermaid
stateDiagram-v2
    zappy_server --> zappy_web_server : bct X Y q0 q1 q2 q3 q4 q5 q6
    zappy_web_server --> zappy_server : bct X Y

    zappy_web_server --> zappy_web_front : Tile information
```
