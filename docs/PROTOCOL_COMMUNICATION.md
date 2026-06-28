# Protocol Communication

Here's how protocol communication works within Zappy:

Firstly there's a handshake between the AI and the server to check for the team.

Once this is completed, anytime there's a modification that requires the GUI to be notified, the server sends over information to all GUI clients.

Most AI commands need to wait for the time limit to expire to be executed.

For example, the `Left` commands needs 7 cycles before being executed.

GUI commands are not subject to this.

---

Below is a simplified communication between AI, Server and GUI.

The AI connect and sends `Left` command.

The GUI connect and sends `bct` command.

```mermaid
sequenceDiagram
    participant AI
    participant Server
    participant GUI

    %% Handshake
    AI->>Server: Connect
    Server->>AI: WELCOME
    AI->>Server: Team Name
    Server->>AI: Spots left in the team
    Server->>AI: Map dimensions

    %% GUI handshake
    GUI->>Server: Connect
    Server->>GUI: WELCOME
    GUI->>Server: GRAPHIC
    Server->>GUI: Lots of informations

    %% Simple AI command
    AI->>Server: Left
    Server->>Server: Player modification
    Server->>GUI: ppo
    Server->>AI: ok

    %% Simple GUI command
    GUI->>Server: bct
    Server->>GUI: bct <team info>
```
