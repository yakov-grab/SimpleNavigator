#include "s21_aco_tsp.h"

bool Ant::construct_solution(float attr_coeff, float trail_level_coeff,
                             std::vector<std::vector<float>> attractivenesses,
                             std::vector<std::vector<float>> trail_levels,
                             const Graph &graph) {
  int graph_size = graph.getSize();
  int current_vertex = 0;
  std::vector<bool> visited_vertices;
  for (int i = 0; i < graph_size; ++i) {
    visited_vertices.push_back(0);
  }
  bool isViableSolution = true;
  for (int i = 0; i < graph_size; ++i) {
    solution.push_back(current_vertex);
    visited_vertices[current_vertex] = 1;
    float sum = 0;
    std::vector<std::pair<float, int>> probs;
    for (int j = 0; j < graph_size; ++j) {
      if (graph.getValue(current_vertex, j) != 0 && visited_vertices[j] != 1) {
        sum += pow(attractivenesses[current_vertex][j], attr_coeff) *
               pow(trail_levels[current_vertex][j], trail_level_coeff);
        probs.push_back(std::pair<float, int>(sum, j));
      }
    }
    for (auto &e : probs) {
      e.first /= sum;
    }
    float r = ((float)rand() / (RAND_MAX));
    int next_vertex = 0;
    int probs_size = probs.size();
    for (int k = 0; k < probs_size; ++k) {
      if (probs[k].first > r) {
        next_vertex = probs[k].second;
        break;
      }
      next_vertex = probs[k].second;
    }
    if (visited_vertices[next_vertex] == 1 && i != graph_size - 1) {
      isViableSolution = false;
      break;
    }
    total_cost += graph.getValue(current_vertex, next_vertex);
    current_vertex = next_vertex;
  }
  if (graph.getValue(solution.back(), 0) != 0) {
    solution.push_back(0);
  } else {
    isViableSolution = false;
  }
  return isViableSolution;
}

void Ant::display() {
  for (auto v : solution) {
    std::cout << v << " -> ";
  }
  std::cout << std::endl << "TOTAL COST: " << total_cost << std::endl;
}

TsmResult Ant::aco_tsp(const Graph &graph, float attractiveness_coefficient,
                       float trail_level_coefficient, int ants_amount,
                       int iterations_amount) {
  // 1. create matrixes of attractivenesses and trail levels
  int graph_size = graph.getSize();
  std::vector<std::vector<float>> attractivenesses;
  std::vector<std::vector<float>> trail_levels;
  for (int i = 0; i < graph_size; ++i) {
    attractivenesses.push_back(std::vector<float>());
    trail_levels.push_back(std::vector<float>());
    for (int j = 0; j < graph_size; ++j) {
      attractivenesses[i].push_back(0);
      trail_levels[i].push_back(0);
    }
  }
  for (int i = 0; i < graph_size; ++i) {
    for (int j = 0; j < graph_size; ++j) {
      if (graph.getValue(i, j) != 0) {
        attractivenesses[i][j] = 2;
        trail_levels[i][j] = 1;
      }
    }
  }

  // Start iterations
  int total_cost_min = 1000000000;
  for (int k = 0; k < iterations_amount; ++k) {
    std::vector<std::vector<float>> delta_trails;
    for (int i = 0; i < graph_size; ++i) {
      delta_trails.push_back(std::vector<float>());
      for (int j = 0; j < graph_size; ++j) {
        delta_trails[i].push_back(0);
      }
    }
    for (int p = 0; p < ants_amount; ++p) {
      Ant ant;
      bool isViable = ant.construct_solution(
          attractiveness_coefficient, trail_level_coefficient, attractivenesses,
          trail_levels, graph);
      if (isViable && ant.total_cost <= total_cost_min) {
        for (int i = 0; i < (int)ant.solution.size() - 1; ++i) {
          delta_trails[ant.solution[i]][ant.solution[i + 1]] +=
              Q_CONST / ant.total_cost;
        }
        total_cost_min = ant.total_cost;
      }
    }
    // update trail levels
    for (int i = 0; i < graph_size; ++i) {
      for (int j = 0; j < graph_size; ++j) {
        trail_levels[i][j] =
            trail_levels[i][j] * (1 - EVAP_CONST) + delta_trails[i][j];
      }
    }
  }

  Ant ant;
  ant.construct_solution(attractiveness_coefficient, trail_level_coefficient,
                         attractivenesses, trail_levels, graph);
  TsmResult result;
  result.distance = ant.total_cost;
  result.vertices = ant.solution;
  return result;
}