#include "s21_graph.h"

Graph::Graph() {
  directed = false;
  weighted = false;
  size = 0;
}

void Graph::loadGraphFromFile(const std::string& filename) {
  std::ifstream cin(filename);
  if (!cin.is_open()) throw std::runtime_error("Can`t open file");

  if (cin.eof()) throw std::runtime_error("Empty file");

  if (size > 0) adjacencyMatrix.clear();

  int fileSize = 0;
  cin >> fileSize;

  size = fileSize;
  if (cin.fail()) throw std::runtime_error("Bad data on file");

  adjacencyMatrix.resize(fileSize);

  for (int i = 0; i < fileSize; i++) {
    for (int j = 0; j < fileSize; j++) {
      int t;
      cin >> t;
      if (cin.fail()) throw std::runtime_error("Bad data on file!");
      adjacencyMatrix[i].push_back(t);
      if (t > 1) weighted = true;
    }
  }
  for (int i = 0; i < size && !directed; i++) {
    for (int j = 0; j < size && !directed; j++) {
      if (adjacencyMatrix[i][j] == adjacencyMatrix[j][i])
        directed = false;
      else
        directed = true;
    }
  }
  cin.close();
}

void Graph::exportGraphToDot(const std::string& filename) {
  std::ofstream cout(filename + ".dot");
  if (!cout.is_open()) throw std::runtime_error("Can`t write file");

  for (int i = 0; i < size; ++i) {
    if (!directed && i == 0)
      cout << "graph graphname"
           << " {" << std::endl;
    else if (i == 0)
      cout << "digraph graphname"
           << " {" << std::endl;
    cout << "	" << i + 1 << ";" << std::endl;
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (adjacencyMatrix[i][j] > 0) {
        if (directed) {
          cout << "	" << i + 1 << " -> " << j + 1
               << " [label = " << adjacencyMatrix[i][j] << "]" << std::endl;
        } else {
          cout << "	" << i + 1 << " -- " << j + 1
               << " [label = " << adjacencyMatrix[i][j] << "]" << std::endl;
        }
      }
    }
  }
  cout << "}" << std::endl;
  cout.close();
}

int Graph::getValue(int row, int column) const {
  if (row < 0 || column < 0 || row >= size || column >= size) {
    throw std::runtime_error("Incorrect row/col");
  }

  return adjacencyMatrix[row][column];
}

int Graph::getGraphSize() const { return (adjacencyMatrix.size()); }

int Graph::getGraphSizeIndex(int i) const {
  if (i < 0 || i > size) {
    throw std::runtime_error("Can't get size");
  }
  return (adjacencyMatrix[i].size());
}
