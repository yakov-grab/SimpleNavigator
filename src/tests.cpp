#include <gtest/gtest.h>

#include "graph/s21_graph.h"
#include "graph_algorithms/s21_graph_algorithms.h"
#include "graph_algorithms/tsm_result.h"
#include "graph_algorithms/s21_aco_tsp.h"

TEST(graph, loadGraphFromFile1) {
  Graph graph;
  EXPECT_ANY_THROW(graph.loadGraphFromFile("i.txt"));
}

TEST(graph, loadGraphFromFile2) {
  Graph graph;
  EXPECT_NO_THROW(graph.loadGraphFromFile("input.txt"));
}

TEST(graph, loadGraphFromFile3) {
  Graph graph;
  Graph graph1 = graph;
  EXPECT_NO_THROW(auto graph3 = std::move(graph1));
}

TEST(graph, exportGraphToDot1) {
  Graph graph;
  graph.loadGraphFromFile("input.txt");
  EXPECT_NO_THROW(graph.exportGraphToDot("output"));
}

TEST(graph, exportGraphToDot2) {
  Graph graph;
  graph.loadGraphFromFile("input2.txt");
  EXPECT_NO_THROW(graph.exportGraphToDot("output2"));
}

TEST(graph, exportGraphToDot3) {
  Graph graph;
  EXPECT_NO_THROW(graph.loadGraphFromFile("input.txt"));
  EXPECT_NO_THROW(graph.exportGraphToDot(""));
}

TEST(graph, TSP) {
  Graph graph;
  graph.loadGraphFromFile("aco.txt");
  unsigned int time_ui = time(NULL);
  srand( time_ui );
  //auto result = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  //EXPECT_TRUE(result.distance > 7.999 && result.distance < 8.0001);
}