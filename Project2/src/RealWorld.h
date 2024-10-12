#ifndef TSP_REALWORLD_H
#define TSP_REALWORLD_H

#include "Graph.h"

using namespace std;

vector<Vertex*> prim(Graph& graph, double n);
void realWorld(Graph &graph, double firstVertex);

#endif //TSP_REALWORLD_H
