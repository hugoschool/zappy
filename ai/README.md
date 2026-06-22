### The Zappy AI's goal is to reach lvl 8 as fast as possible.
In order to reach this goal, there must be at least 6 players reaching lvl 7 and then elevating together.
The game works by frames - meaning, each action a player does takes x frames to complete
To incantate, a player needs the necessary minerals for each level of elevation.
Incantation takes 300 f (frames)
Over the course of its life, a player will consume food. Each food lasts for 120f
By taking the actions of looking (7f), moving(7f) and taking objects (7f) a player can gather those minerals and food, and eventually use them or set them down(7f)
So, a team's goal is to have 6 of its players reach lvl 8, effectively ending the simulation
Consequently, a team will try to dispatch its players effectively in order to gather ressources as quick as possible and begin elevating asap.

| Elevation Lvl | Players | linemate | deraumere | sibur | mendiane | phiras | thystame |
| ------------- | ------- | -------- | --------- | ----- | -------- | ------ | -------- |
|      2        | 1       | 1        | 0         | 0     | 0        | 0      | 0        |
|      3        | 2       | 1        | 1         | 1     | 0        | 0      | 0        |
|      4        | 1       | 2        | 0         | 1     | 0        | 2      | 0        |
|      5        | 1       | 1        | 1         | 2     | 0        | 1      | 0        |
|      6        | 1       | 1        | 2         | 1     | 3        | 0      | 0        |
|      7        | 1       | 1        | 2         | 3     | 0        | 1      | 0        |
|      8        | 1       | 2        | 2         | 2     | 2        | 2      | 1        |
# Our strategy
## POC: Perfected Oligarch Communism
Our strategy -- for the time being -- is set around a main group which will be the one elevating, and a subgroup, bred by the main group, and whose job will be to gather ressources for the main group.



### Ideas:
-> In case a "parrot" type player exists in an opposing team -- an AI whose sole job is to repeat enemy broadcasts (it wouldn't be useless to implement one ourselves btw) -- we should make every player check if the broadcast they are receiving has already been sent, if this is the case, ignore it.
If a broadcast needs to be sent many times, we should add a specific key, may it be the time of the message or any other constantly-moving data, to ensure a message is parrot-sent

