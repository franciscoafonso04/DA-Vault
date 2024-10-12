#ifndef TSP_OTHERHEURISTICS_H
#define TSP_OTHERHEURISTICS_H

#include "Graph.h"
using namespace std;

TourResult christofidesAlgorithm(Graph& graph);
TourResult cheapestInsertion(Graph* graph);

#endif //TSP_OTHERHEURISTICS_H
