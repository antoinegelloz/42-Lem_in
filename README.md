# Lem_in
Lem_in is an algorithm project about solving a special case of a maximum flow problem in network optimization.</br>
The goal is to find a feasible flow of ants through an anthill that minimizes the number of movement rounds.</br>
An anthill is described as a network composed of 'rooms' (graph nodes) and 'tunnels' (graph edges) linking the rooms together.</br>
The real trouble begins when each room can welcome only ONE ant at a time (except for Start and End).</br>
A round ends when no more ants are able to move any further.

### Building
`make` is used to build the `libft.a` static library and the `lem-in` binary. Execute the following commands to build the project:
```
cd 42-Lem_in
make
```

### Usage
The `lem-in` binary reads `stdin` for a map with a precise template:
```
./lem-in < maps/demo_map
```
