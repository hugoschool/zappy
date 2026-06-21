# Zappy

Network game where AIs battle each other

2nd Year End project at EPITECH

Main repository: https://github.com/freaky-family/zappy

<!-- TODO: could be cool to have a screenshot of the GUI here -->

## Quick introduction

According to the subject, "Zappy" is a game where several teams confront each other on a tile map containing resources.

The goal is to collect enough resources for 6 players of the same team to reach the maximum level (level 8).

The "players" are represented by AIs that automatically move around the terrain. They can interact with the terrain, push other players etc.

## Build

You can build everything with:
```sh
make
```

However you can build each part seperately:
```sh
make ai
make gui
make server
```

> [!NOTE]
> Requirements for **GUI:**
> - Raylib 6.0
> - raylib-cpp 6.0.1

You can always verify the building process in `.github/workflows/build.yml`.

## Documentation

More documentation is available in the `docs/` folder.

## Group

Server team:
- Hugo ARNAL
- Bastien SUKIENNIK

GUI team:
- Esteban HAZANAS
- Sacha DEFOSSEZ

AI team:
- Alexandre KUBIACZYK
- Nadal BERTHELON

Bonus:
- Hector CORDAT-BOURSIAC
