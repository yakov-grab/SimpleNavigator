#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <math.h>

#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

class Graph {
 public:
  Graph();

  int getSize() const { return size; }
  void loadGraphFromFile(const std::string& filename);
  void exportGraphToDot(const std::string& filename);
  std::vector<std::vector<int>> getMatrix() { return adjacencyMatrix; }
  int getValue(int row, int col) const;
  int getGraphSize() const;
  int getGraphSizeIndex(int i) const;

 private:
  int size;
  std::vector<std::vector<int>> adjacencyMatrix;
  bool weighted;
  bool directed;
};

#endif
