#ifndef CONSOLE_H
#define CONSOLE_H

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"
#include "../graph_algorithms/tsm_result.h"

class Console {
 public:
  Console() {}
  ~Console() {}
  void actionMenu();

 private:
  Graph g;
  bool graphLoad = false;

  int menu();
  void loadGraph();
  void checkLoad();
  void printVector(const std::vector<int> vec);
  void printVec(const std::vector<std::vector<int>> vec);
  void BFS();
  void DFS();
  void Dijkstra();
  void FloydWarshall();
  void SpanningTree();
  void Salesman();
  void Research();
};
#endif