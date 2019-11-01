#!/usr/bin/env python3
try:
    import sys
    import json
    import argparse
    import contextlib

    with contextlib.redirect_stdout(None):
        import networkx as nx
        import matplotlib.pyplot as plt
except ModuleNotFoundError:
    print("Networkx and matplotlib not installed")
    exit(1)

col_path = ['green', 'red', 'orange', 'magenta', 'cyan', 'brown', 'blue', 'black',
            '#f08c00', '#308bc0', '#f9c030', '#23f012', '#497663', '#ec5952', '#db8fb0',
            '#afc58c', '#08ea07', '#3e60f3', '#9d5d80', '#701488', '#a78923', '#d461f8',
            '#0628c4', '#2f8bdc', '#1abf73', '#04edc1', '#dffe5d', '#fbfbad', '#b26258',
            '#d2881e', '#95d6ae', 'grey']

def draw_graph_nodes(G, paths, col_path, draw_grey):
    n = 0
    pos = nx.spectral_layout(G);
    flag = False
    for node in G.nodes:
        if node == paths[0][0]:
            nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                   node_color=col_path[0], node_size=20)
        elif node == paths[0][1]:
            nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                   node_color=col_path[1], node_size=20)
        for i in range(1, len(paths)):
            if node in paths[i]:
                nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                       node_color=col_path[i+1], node_size=20)
                flag = False
                break
            else:
                flag = True
        if flag and draw_grey:
            nx.draw_networkx_nodes(G, pos, nodelist=[node],
                                   node_color=col_path[-1],
                                   node_size=2, alpha=0.1)
        flag = False
        n += 1
        if n == len(G.nodes):
            break

def draw_graph_edges(G, paths, col_path, draw_grey):
    e = 0
    flag = False
    pos = nx.spectral_layout(G)
    for edge in G.edges:
        for i in range(1, len(paths)):
            if (
                    (edge[0] in paths[i] and edge[1] in paths[i])
                    or (edge[0] in paths[0] and edge[1] in paths[i])
                    or (edge[0] in paths[i] and edge[1] in paths[0])
            ):
                nx.draw_networkx_edges(G, pos, edgelist=[edge],
                                       edge_color=col_path[i+1])
                flag = False
                break
            else:
                flag = True
        if flag and draw_grey:
            nx.draw_networkx_edges(G, pos, edgelist=[edge],
                                   edge_color=col_path[-1], alpha=0.1)
        flag = False
        e += 1
        if e == len(G.edges):
            break

class Parse:
    def __init__(self, draw_grey=None):
        self.name = "Graph"
        self.G = nx.Graph(name=self.name)
        if draw_grey is None:
            self.draw_grey = False
        else:
            self.draw_grey = draw_grey
        self.connections = []
        self.nodes = []
        self.start = None
        self.end = None
        self.num_ants = 0
        self.max_moves = None
        self.ants = {}
        self.antmoves = []
        self.paths = []
        self.nodes_colors = []
        self.edges_colors = []

    def add_room(self, line, start_end):
        self.nodes.append(line)
        n = line.split(' ')
        if start_end == -1 and 'red' not in self.nodes_colors:
            self.G.add_node(n[0], weight=2)
            self.end = n[0]
            self.nodes_colors.append('red')
        elif start_end == 1 and 'green' not in self.nodes_colors:
            self.G.add_node(n[0], weight=2)
            self.start = n[0]
            self.nodes_colors.append('green')
        else:
            self.G.add_node(n[0], weight=1)
            self.nodes_colors.append('grey')

    def add_edge(self, line):
        self.connections.append(line)
        n = line.split('-')
        self.G.add_edge(n[0], n[1], capacity=1, weight=1)
        self.edges_colors.append("grey")

    def add_ant(self, line):
        for move in line.split(" "):
            a = move.split("-")
            if a[0] not in self.ants:
                self.ants[a[0]] = [a[1]]
            else:
                self.ants[a[0]].append(a[1])

    def read_input(self, argfile):
        start_end = 0
        lines = [line.rstrip("\n") for line in argfile]
        num_lines = len(lines)
        n = 0
        print(*lines,sep= "\n")
        for line in lines:
            if line == "":
                pass
            elif n == 0 and line.isdigit():
                self.num_ants = int(line)
            elif line[0] == '#':
                if line == "##start":
                    start_end = 1
                elif line == "##end":
                    start_end = -1
                else:
                    start_end = 0
            elif line.count(" ") == 2:
                self.add_room(line, start_end)
            elif "L" not in line and "-" in line:
                self.add_edge(line)
            elif "L" in line and "-" in line:
                self.antmoves.append(line)
                self.add_ant(line)
            n += 1
        tmp = []
        if (len(self.antmoves) > 0):
            for move in self.antmoves[0].split(" "):
                tmp.append(move.split("-")[0])
        self.paths.append([self.start, self.end])
        for ant in tmp:
            self.paths.append(self.ants[ant][:-1])

    def draw_graph(self):
        draw_graph_nodes(self.G, self.paths, col_path, self.draw_grey)
        draw_graph_edges(self.G, self.paths, col_path, self.draw_grey)
        plt.axis('off')
        plt.show()

def main():
    parser = argparse.ArgumentParser(description="Visualize the output of a lem-in binary using GraphViz and NetworkX")
    parser.add_argument("-a", "--draw-all", help="Draw unused nodes and edges", action="store_true")
    args = parser.parse_args()
    loops = Parse(draw_grey=args.draw_all)
    loops.read_input(sys.stdin)
    loops.draw_graph()

if __name__ == '__main__':
    main()
