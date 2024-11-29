#include "console.h"

#include <exception>
#include <iostream>

int Console::menu() {
  int action;
  std::cout << "Choose action: enter a number" << std::endl;
  std::cout << "0. Exit" << std::endl;
  std::cout << "1. Load graph from file" << std::endl;
  std::cout << "2. BFS" << std::endl;
  std::cout << "3. DFS" << std::endl;
  std::cout << "4. Shortest path between 2 vertices (Dijkstra)" << std::endl;
  std::cout << "5. Shortest path between all vertices (Floyd-Warshall)"
            << std::endl;
  std::cout << "6. Least spanning tree (Prim)" << std::endl;
  std::cout << "7. Salesman problem" << std::endl;
  std::cout << "8. Research" << std::endl;
  std::cin >> action;

  return (action);
}

void Console::actionMenu() {
  try {
    while (true) {
      std::cout << std::endl;
      int action = menu();
      switch (action) {
        case 1:
          loadGraph();
          break;
        case 2:
          checkLoad();
          BFS();
          break;
        case 3:
          checkLoad();
          DFS();
          break;
        case 4:
          checkLoad();
          Dijkstra();
          break;
        case 5:
          checkLoad();
          FloydWarshall();
          break;
        case 6:
          checkLoad();
          SpanningTree();
          break;
        case 7:
          checkLoad();
          Salesman();
          break;
        case 8:
          checkLoad();
          Research();
          break;
        case 0:
          exit(EXIT_SUCCESS);
          break;
        default:
          std::cout << "Indefinite action" << std::endl;
          actionMenu();
          break;
      }
    }
  } catch (std::exception &e) {
    std::cout << "What's wrong?" << std::endl;
    std::cin.clear();
    std::cin.ignore(10, '\n');
    actionMenu();
  }
}

void Console::loadGraph() {
  try {
    std::cout << std::endl;
    std::cout << "Enter file path:" << std::endl;
    std::string path;
    std::cin >> path;
    g.loadGraphFromFile(path);
    graphLoad = true;
    std::cout << std::endl;
    std::cout << "Download successful!" << std::endl;
    std::cout << std::endl;
    std::cout << "Do you want to use dot file? enter a number" << std::endl;
    std::cout << "1 = YES || 0 = NO" << std::endl;
    int action;
    std::cin >> action;
    if (action == 1) {
      std::cout << "Enter file name:" << std::endl;
      std::string name;
      std::cin >> name;
      g.exportGraphToDot(name);
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    loadGraph();
  }
}

void Console::checkLoad() {
  if (!graphLoad) {
    std::cout << std::endl;
    std::cout << "Graph not loaded" << std::endl;
    std::cout << std::endl;
    actionMenu();
  }
}

void Console::printVector(const std::vector<int> vec) {
  for (auto it : vec) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
}

void Console::printVec(const std::vector<std::vector<int>> vec) {
  for (unsigned long i = 0; i < vec.size(); i++) {
    for (unsigned long j = 0; j < vec.size(); j++) {
      std::cout << vec[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void Console::BFS() {
  try {
    std::cout << std::endl;
    std::cout << "Enter starting vertex" << std::endl;

    int vertex;
    std::cin >> vertex;
    std::cout << std::endl;
    printVector(GraphAlgorithms::breadthFirstSearch(g, vertex));
    std::cout << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    BFS();
  }
}

void Console::DFS() {
  try {
    std::cout << std::endl;
    std::cout << "Enter starting vertex" << std::endl;

    int vertex;
    std::cin >> vertex;
    std::cout << std::endl;
    printVector(GraphAlgorithms::depthFirstSearch(g, vertex));
    std::cout << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    DFS();
  }
}

void Console::Dijkstra() {
  try {
    std::cout << std::endl;

    std::cout << "Enter starting vertex" << std::endl;
    int vertex;
    std::cin >> vertex;
    std::cout << std::endl;

    std::cout << "Enter ending vertex" << std::endl;
    int vertex2;
    std::cin >> vertex2;
    std::cout << std::endl
              << GraphAlgorithms::getShortestPathBetweenVertices(g, vertex,
                                                                 vertex2);
    std::cout << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    actionMenu();
  }
}

void Console::FloydWarshall() {
  try {
    std::cout << std::endl;
    printVec(GraphAlgorithms::getShortestPathsBetweenAllVertices(g));
    std::cout << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    actionMenu();
  }
}

void Console::SpanningTree() {
  try {
    std::vector<std::vector<int>> matrix =
        GraphAlgorithms::getLeastSpanningTree(g);
    std::cout << "graph:" << std::endl;
    GraphAlgorithms::printGraph(g);
    std::cout << "mst:" << std::endl;
    printVec(matrix);

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    actionMenu();
  }
}

void Console::Salesman() {
  try {
    std::cout << std::endl;
    unsigned int time_ui = time(NULL);
    srand(time_ui);
    auto result = GraphAlgorithms::SolveTravelingSalesmanProblem(g);
    for (auto v : result.vertices) {
      std::cout << v << " -> ";
    }
    std::cout << std::endl << "TOTAL COST: " << result.distance << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    actionMenu();
  }
}

void Console::Research() {
  try {
    std::cout << std::endl
              << "How many times to run the research?" << std::endl;
    int N;
    std::cin >> N;
    if (N > 0 && N <= 1000) {
      double timeAnt = 0.0;
      double timeSecondAlg = 0.0;
      double timeThierdAlg = 0.0;
      TsmResult ant;
      TsmResult secondAlg;
      TsmResult thierdAlg;
      clock_t start, end;

      start = clock();
      for (int i = 0; i < N; ++i) {
        if (i == 0) {
          ant = GraphAlgorithms::SolveTravelingSalesmanProblem(g);
        } else {
          TsmResult tmp = GraphAlgorithms::SolveTravelingSalesmanProblem(g);
          if (tmp.distance < ant.distance) {
            ant = tmp;
          }
        }
      }
      end = clock();
      timeAnt = ((double)end - start) / ((double)CLOCKS_PER_SEC);

      start = clock();
      for (int i = 0; i < N; ++i) {
        if (i == 0) {
          secondAlg = GraphAlgorithms::secondAlg(g);
        } else {
          TsmResult tmp = GraphAlgorithms::secondAlg(g);
          if (tmp.distance < secondAlg.distance) {
            secondAlg = tmp;
          }
        }
      }
      end = clock();
      timeSecondAlg = ((double)end - start) / ((double)CLOCKS_PER_SEC);

      start = clock();
      for (int i = 0; i < N; ++i) {
        if (i == 0) {
          thierdAlg = GraphAlgorithms::thierdAlg(g);
        } else {
          TsmResult tmp = GraphAlgorithms::thierdAlg(g);
          if (tmp.distance < thierdAlg.distance) {
            thierdAlg = tmp;
          }
        }
      }
      end = clock();
      timeThierdAlg = ((double)end - start) / ((double)CLOCKS_PER_SEC);

      std::cout << std::endl << "Ant Algoritm" << std::endl;
      std::cout << "Starts: " << N << std::endl;
      std::cout << "Time: " << timeAnt << std::endl
                << "Distance: " << ant.distance << std::endl;

      std::cout << std::endl << "Second Algoritm" << std::endl;
      std::cout << "Starts: " << N << std::endl;
      std::cout << "Time: " << timeSecondAlg << std::endl
                << "Distance: " << secondAlg.distance << std::endl;

      std::cout << std::endl << "Thierd Algoritm" << std::endl;
      std::cout << "Starts: " << N << std::endl;
      std::cout << "Time: " << timeThierdAlg << std::endl
                << "Distance: " << thierdAlg.distance << std::endl;

    } else {
      std::cout << std::endl << "Enter a number from 1 to 1000" << std::endl;
    }
    actionMenu();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    actionMenu();
  }
}
