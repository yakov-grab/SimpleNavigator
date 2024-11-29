#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include <limits>
#include <set>
#include <vector>

#include "../graph/s21_graph.h"
#include "../queue/Queue.hpp"
#include "../stack/Stack.hpp"
#include "s21_aco_tsp.h"
#include "tsm_result.h"

class GraphAlgorithms {
 public:
  static std::vector<int> depthFirstSearch(Graph &graph, int startVertex);
  static std::vector<int> breadthFirstSearch(Graph &graph, int startVertex);
  static void printGraph(Graph &graph);
  static std::vector<std::vector<int>> getLeastSpanningTree(Graph &graph);
  static int getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                            int vertex2);
  static std::vector<std::vector<int>> getShortestPathsBetweenAllVertices(
      Graph &graph);
  static TsmResult SolveTravelingSalesmanProblem(Graph &graph);
  static TsmResult secondAlg(Graph &graph);
  static TsmResult thierdAlg(Graph &graph);
};

#endif
