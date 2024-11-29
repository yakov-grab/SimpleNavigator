#ifndef TSM_RESULT_H
#define TSM_RESULT_H

#include <vector>
struct TsmResult {
  std::vector<int> vertices;  // an array with the route you are looking for
                              // (with the vertex traverse order). Instead of
                              // int* you can use std::vector<int>
  double distance;            // the length of this route
};

#endif