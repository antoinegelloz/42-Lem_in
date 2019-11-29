# Lem_in
Lem_in is an algorithm project about solving a special case of a maximum flow problem in network optimization.</br>
The goal is to find the best flow of ants through an anthill that minimizes the number of movement rounds.</br>
An anthill is described as a network composed of 'rooms' (graph nodes) and 'tunnels' (graph edges) linking the rooms together.</br>
The real trouble begins when each room can welcome only one ant at a time (except for start and end).</br>
A round ends when no more ants are able to move any further.

![demo](visual/lemin.gif)

## Algorithm
```
Modified Edmonds-Karp with BFS searching for the paths minimizing the lines of output

function main(options):
	parse the arguments for any options
	parse the file from stdin (get ants number, rooms and tunnels)
	build the graph with an adjacency list
	if (parsing error):
		print error and exit
	initialize paths list to null
	paths = find_paths(graph)
	if (no solution is found):
		print error and exit
	print the file on stdout
	assign each ant to a path
	let the ants pass into the graph by printing one line of output for each round
	display any options for arguments

function find_paths(graph):
	initialize paths list to null
	new_path = bfs(graph)
	append new_path to paths
	reduce capacities of the new_path forward edges
	increase capacities of the new_path backward edges
	compute the initial lines of output using only this first path
	point to the first path with selected_path
	while (selected_path did not reach the end of the paths list):
		store the previous number of paths found
		new_path = bfs(graph, selected_path)
		compute the new lines of output
		if (the new output is minimized):
			update the count of lines of output
			append new_paths to paths
			reduce capacities of the new_path forward edges to 0
			increase capacities of the new_path backward edges to 2
			selected_path to first path
		else:
			discard new_path
			selected_path to next path
	return (paths)

function bfs(graph, selected_path):
	create a queue and add start_room
	create a prev[size of graph] array to keep track of previous rooms when enqueued
	while (queue is not empty):
		room = dequeue(queue)
		for each (neighbours of room NOT already enqueued):
			if (room is NOT on selected_path AND NOT end_room):
				if (neighbour is on selected_path AND NOT a start_room neighbour):
					mark neighbour as visited
					mark neighbour as already enqueued
					update prev[neighbour] = room
					select neighbour2 as the previous room of neighbour on the selected_path
					enqueue(neighbour, neighbour2)
				else if (neighbour is NOT visited):
					enqueue(room, neighbour)
			else if (room is on selected_path
					AND (edge to neighbour has a capacity of 2 AND NOT start_room
						|| edge to neighbour has a capacity of 1 AND NOT visited)):
				enqueue(room, neighbour)
	return (reconstruct_path(graph, prev))

function reconstruct_path(graph, prev):
	initialize new_paths list to null
	room = end_room
	while (room exists):
		add room to new_path list
		room = prev[room]
	if (the first room of new_path is start):
		reset all rooms visited on the new_path
		return (new_path)
	else:
		reset all rooms visited
		return (null)

function enqueue(room, neighbour):
	mark neighbour as visited
	mark neighbour as already enqueued
	update prev[neighbour] = room
	enqueue(neighbour)
```

## Building
`make` is used to build the `libft.a` static library and the `lem-in` binary. To build the project, Execute the following commands:
```
cd 42-Lem_in
make
```
## Dependencies (only for the visual)
* PHP
* Google Chrome

## Usage
A map with a precise format is sent to the `lem-in` program as `stdin` input:
```
./lem-in [-h --help] [-a --anthill] [-p --paths] [-v --visual] < maps/demo_map
```
### Map format
```
5		<< ants number
##start		<< start room is following
r0 1 2
r1 2 3
r2 3 4
r3 4 5
r4 3 5
r5 6 7
r6 8 9
r7 7 9
##end		<< end room is following
r8 90 1
r0-r1		<< tunnels
r1-r2
r2-r8
r0-r6
#comment	<< optional comments can at any line
r6-r7
r1-r6
r1-r4
r4-r8
r0-r3
r3-r2
r2-r5
r5-r8
```
Many examples are provided in the `/maps` repository.

### Options
* -h --help : Display usage
* -a --anthill : Display the anthill rooms and tunnels in a table
* -p --paths : Display the paths found by the algorithm
* -v --visual : Display the visual in a new Google Chrome tab

## Output
The output of the program is divided in two parts:
* the file read from `stdin`
* one round - movements of ants - per line (output to minimize)

### Example
```
5
##start
r0 1 2
r1 2 3
r2 3 4
r3 4 5
r4 3 5
r5 6 7
r6 8 9
r7 7 9
##end
r8 90 1
r0-r1
r1-r2
r2-r8
r0-r6
r6-r7
r1-r6
r1-r4
r4-r8
r0-r3
r3-r2
r2-r5
r5-r8

L1-r3 L2-r1				<< round 0
L1-r2 L2-r4 L3-r3 L4-r1			<< round 1
L1-r8 L2-r8 L3-r2 L4-r4 L5-r3		<< round 2
L3-r8 L4-r8 L5-r2			<< round 3
L5-r8					<< round 4
```
