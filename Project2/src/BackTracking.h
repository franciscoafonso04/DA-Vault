#ifndef TSP_BACKTRACKING_H
#define TSP_BACKTRACKING_H

#include "Graph.h"


using namespace std;



TourResult findTSP(Graph* graph);
void tspUtil(Graph* graph, Vertex *v, double currentWeight, int count, double &minWeight, std::vector<Vertex*>& currentPath, std::vector<Vertex*>& bestPath);

#endif //TSP_BACKTRACKING_H
