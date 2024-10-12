//
// Created by alex-uni on 03-05-2024.
//

#ifndef TSP_TRIANGULARAPPROXIMATION_H
#define TSP_TRIANGULARAPPROXIMATION_H

#include "Graph.h"

using namespace std;

TourResult triangularApproximation(Graph* graph);
vector<Vertex*> prim(const Graph* graph);


#endif //TSP_TRIANGULARAPPROXIMATION_H
