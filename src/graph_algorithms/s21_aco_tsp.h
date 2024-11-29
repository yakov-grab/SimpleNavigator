#ifndef S21_ACO_TSP_H
#define S21_ACO_TSP_H

#include <math.h>

#include <ctime>
#include <random>
#include <vector>

#include "../graph/s21_graph.h"
#include "../graph_algorithms/s21_graph_algorithms.h"
#include "tsm_result.h"

#define EVAP_CONST 0.05
#define Q_CONST 10.0

class Ant {
 private:
  std::vector<int> solution;
  int total_cost;

 public:
  Ant() : total_cost(0) {}
  bool construct_solution(float attr_coeff, float trail_level_coeff,
                          std::vector<std::vector<float>> attractivenesses,
                          std::vector<std::vector<float>> trail_levels,
                          const Graph &graph);
  void display();
  static TsmResult aco_tsp(const Graph &graph, float attractiveness_coefficient,
                           float trail_level_coefficient, int ants_amount,
                           int iterations_amount);
};
#endif