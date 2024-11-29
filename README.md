# SimpleNavigator

## Project Description
This project is an implementation of basic graph algorithms, such as depth-first and breadth-first traversal, shortest paths, minimum spanning tree construction, and traveling salesman problem solving.

## Features
- graph loading and export:
    - graph loading from file in adjacency matrix format
    - graph export to file in dot format

- graph traversal:
    - depth-first search (DFS)
    - breadth-first search (BFS)

- shortest path search:
    - Dijkstra algorithm (find shortest path between two vertices)
    - Floyd-Warshall algorithm (find shortest paths between all pairs of vertices)

- Minimum spanning tree construction:
    - Prim's algorithm (smallest spanning tree construction)

- Traveling salesman problem

- Additional:
- comparison of performance of different algorithms for traveling salesman problem

## Graph representation
Graphs in the project are represented as an adjacency matrix, where each cell [i][j] contains the weight of the edge between vertices i and j. If there is no edge, the weight is zero.

## Console interface
The console interface provides the following capabilities:
- loading the original graph from a file
- breadth-first traversal of the graph with the output of the traversal result to the console
- depth-first traversal of the graph with the output of the traversal result to the console
- finding the shortest path between any two vertices with the output of the result to the console
- finding the shortest paths between all pairs of vertices in the graph with the output of the resulting matrix to the console
- finding the minimum spanning tree in the graph with the output of the resulting adjacency matrix to the console
- solving the traveling salesman problem with the output of the resulting route and its length to the console
- loading the original graph from a file
- breadth-first traversal of the graph with the output of the traversal result to the console
- depth-first traversal of the graph with the output of the traversal result to the console
- finding the shortest path between any two vertices with the output of the result to the console
- finding the shortest paths between all pairs of vertices in the graph with the output of the resulting matrix to the console
- finding the minimum spanning tree in the graph with output of the resulting adjacency matrix to the console
- solving the traveling salesman problem


## Build and install

To build and install the program, use Makefile with a standard set of targets for GNU programs:
- **all** - build the main libraries.
- **clean** - deletes generated files and build directories.
- **test** - build and run tests.
- **s21_graph.a** - builds the s21_graph library.
- **s21_graph_algorithms.a** - builds the s21_graph_algorithms library.
- **leaks** - runs tests with memory leaks check.
