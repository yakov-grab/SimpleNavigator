#include "s21_graph_algorithms.h"

std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph,
                                                   int startVertex) {
  if (startVertex < 1 || startVertex > graph.getSize()) {
    throw std::invalid_argument("Wrong vertex");
  }

  std::vector<int> result;
  std::vector<bool> visitedVertex(graph.getSize());
  ft::Stack<int> vertexStack;
  visitedVertex[startVertex - 1] = true;
  vertexStack.push(startVertex - 1);

  while (!vertexStack.empty()) {
    result.push_back(vertexStack.peek() + 1);
    int current = vertexStack.top();
    vertexStack.pop();

    for (int i = graph.getSize() - 1; i >= 0; i--) {
      if (graph.getValue(current, i) && !visitedVertex[i]) {
        vertexStack.push(i);
        visitedVertex[i] = true;
      }
    }
  }

  return result;
}

std::vector<int> GraphAlgorithms::breadthFirstSearch(Graph &graph,
                                                     int startVertex) {
  if (startVertex < 1 || startVertex > graph.getSize()) {
    throw std::invalid_argument("Wrong vertex");
  }

  std::vector<int> result;
  std::vector<bool> visitedVertex(graph.getSize());
  ft::Queue<int> vertexStack;

  visitedVertex[startVertex - 1] = true;
  vertexStack.push(startVertex - 1);

  while (!vertexStack.empty()) {
    result.push_back(vertexStack.peek() + 1);
    int current = vertexStack.front();
    vertexStack.pop();

    for (int i = 0; i < graph.getSize(); i++) {
      if (graph.getValue(current, i) && !visitedVertex[i]) {
        vertexStack.push(i);
        visitedVertex[i] = true;
      }
    }
  }

  return result;
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  if (vertex1 > graph.getSize() || vertex2 > graph.getSize() || vertex1 < 1 ||
      vertex2 < 1) {
    throw std::invalid_argument("Wrong vertexes");
  }

  std::vector<int> path(graph.getSize(), INT32_MAX);
  std::vector<bool> visitedVertex(graph.getSize());
  ft::Queue<int> vertexStack;

  vertexStack.push(vertex1 - 1);
  visitedVertex[vertex1 - 1] = true;
  path.at(vertex1 - 1) = 0;

  while (!vertexStack.empty()) {
    int current = vertexStack.front();
    vertexStack.pop();

    for (int i = 0; i < graph.getSize(); i++) {
      if (graph.getValue(current, i) && !visitedVertex[i] &&
          path[i] > (path[current] + graph.getValue(current, i))) {
        path[i] = path[current] + graph.getValue(current, i);
        visitedVertex[current] = true;
        if (i != (vertex2 - 1)) vertexStack.push(i);
      }
    }
  }
  return path[vertex2 - 1] == INT32_MAX ? 0 : path[vertex2 - 1];
}

std::vector<std::vector<int>>
GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  std::vector<std::vector<int>> result = graph.getMatrix();
  std::vector<std::vector<int>> newResult = graph.getMatrix();
  for (int k = 0; k < graph.getSize(); k++) {
    for (int i = 0; i < graph.getSize(); i++) {
      for (int j = 0; j < graph.getSize(); j++) {
        newResult[i][j] =
            std::min(newResult[i][j], (result[i][k] + result[k][j]));
      }
    }
  }
  return newResult;
}

void GraphAlgorithms::printGraph(Graph &graph) {
  for (int i = 0; i < graph.getSize(); i++) {
    for (int j = 0; j < graph.getSize(); j++) {
      std::cout << graph.getValue(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<int>> GraphAlgorithms::getLeastSpanningTree(
    Graph &graph) {
  int v = graph.getSize();
  int edge;
  int selected[v];
  memset(selected, false, sizeof(selected));
  edge = 0;
  selected[0] = true;
  int x;
  int y;
  std::vector<std::vector<int>> matrix(v, std::vector<int>(v, 0));

  while (edge < v - 1) {
    int min = INT32_MAX;
    x = 0;
    y = 0;
    for (int i = 0; i < v; i++) {
      if (selected[i]) {
        for (int j = 0; j < v; j++) {
          if (!selected[j] && graph.getValue(i, j)) {
            if (min > graph.getValue(i, j)) {
              min = graph.getValue(i, j);
              x = i;
              y = j;
            }
          }
        }
      }
    }
    selected[y] = true;
    edge++;
    matrix[x][y] = graph.getValue(x, y);
  }
  return (matrix);
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  return Ant::aco_tsp(graph, 1, 1, 100, 10);
}

TsmResult GraphAlgorithms::secondAlg(Graph &graph) {
  TsmResult result;
  std::vector<std::vector<int>> matr = getLeastSpanningTree(graph);
  std::vector<std::vector<int>> matr2 = graph.getMatrix();

  if (matr2[matr2.size() - 1][0])
    matr[matr.size() - 1][0] = matr2[matr2.size() - 1][0];

  std::vector<bool> visitedVertex(matr.size());
  ft::Stack<int> vertexStack;
  visitedVertex[0] = true;
  vertexStack.push(0);

  while (!vertexStack.empty()) {
    result.vertices.push_back(vertexStack.peek() + 1);
    int current = vertexStack.top();
    vertexStack.pop();

    for (int i = matr.size() - 1; i >= 0; i--) {
      if (matr[current][i] && !visitedVertex[i]) {
        result.distance += matr[current][i];
        vertexStack.push(i);
        visitedVertex[i] = true;
      }
    }
  }

  if (matr[matr.size() - 1][0]) {
    result.vertices.push_back(1);
    result.distance += matr[matr.size() - 1][0];
  }
  return result;
}

TsmResult GraphAlgorithms::thierdAlg(Graph &graph) {
  TsmResult result;
  std::vector<std::vector<int>> matr = getLeastSpanningTree(graph);
  std::vector<std::vector<int>> matr2 = graph.getMatrix();

  if (matr2[matr2.size() - 1][0])
    matr[matr.size() - 1][0] = matr2[matr2.size() - 1][0];

  std::vector<bool> visitedVertex(matr.size());
  ft::Queue<int> vertexStack;

  visitedVertex[0] = true;
  vertexStack.push(0);

  while (!vertexStack.empty()) {
    result.vertices.push_back(vertexStack.peek() + 1);
    int current = vertexStack.front();
    vertexStack.pop();

    for (unsigned long i = 0; i < matr.size(); i++) {
      if (matr[current][i] && !visitedVertex[i]) {
        result.distance += matr[current][i];
        vertexStack.push(i);
        visitedVertex[i] = true;
      }
    }
  }

  if (matr[matr.size() - 1][0]) {
    result.vertices.push_back(1);
    result.distance += matr[matr.size() - 1][0];
  }
  return result;
}
