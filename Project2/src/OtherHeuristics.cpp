#include "OtherHeuristics.h"
#include "stack"

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds the weight of the edge connecting two given vertices.
 * @details Time Complexity: O(E).
 * @param graph Graph.
 * @param v Origin vertex.
 * @param u Destination vertex.
 * @return the weight of the edge in double format by performing haversine.
 * */

double getWeight(Graph graph, Vertex* v, Vertex* u) {
    Edge* edge = graph.findEdge(v->getInfo(), u->getInfo());
    if (edge != nullptr) return edge->getWeight();
    return haversine(v, u);
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds a solution to the TSP using the cheapest insertion algorithm.
 * @details Time Complexity: O(V² * E).
 * @param graph Pointer to the graph.
 * @return the tour and its total distance in the format of TourResult struct.
 * */
TourResult cheapestInsertion(Graph* graph) {
    vector<Vertex*> tour;

    tour.push_back(graph->getVertexSet()[0]);

    double minDist = INT_MAX;
    Vertex* aux = nullptr;

    for (auto v : graph->getVertexSet()) { // V * E
        double weight = getWeight(*graph, graph->getVertexSet()[0], v);
        if (weight < minDist) {
            minDist = weight;
            aux = v;
        }
    }

    tour.push_back(aux);

    while (tour.size() < graph->getVertexSet().size()) {
        aux = graph->findVertex(0);
        minDist = INT_MAX;

        for (auto v : graph->getVertexSet()) {
            if (find(tour.begin(), tour.end(), v) == tour.end()) {
                double nearestDist = INT_MAX;

                for (auto j : tour) {
                    double dist = getWeight(*graph, j, v);
                    if (dist < nearestDist) {
                        nearestDist = dist;
                        aux = v;
                    }
                }

                if (nearestDist < minDist) {
                    minDist = nearestDist;
                }
            }
        }

        unsigned int idx = 0;
        double minWeight = INT_MAX;

        for (unsigned int i = 0; i < tour.size(); i++) {
            unsigned int nextIndex = i + 1;
            if (nextIndex > tour.size() - 1) nextIndex = 0;
            double weight = getWeight(*graph, tour[i], aux) + getWeight(*graph, aux, tour[nextIndex]) - getWeight(*graph, tour[i], tour[nextIndex]);
            if (weight < minWeight) {
                minWeight = weight;
                idx = nextIndex;
            }
        }

        tour.insert(tour.begin() + idx, aux);
    }


    TourResult result;
    result.tour = tour;

    for (unsigned int i = 0; i < tour.size() - 1; i++) {
        result.totalDistance += getWeight(*graph, tour[i], tour[i + 1]);
    }

    return result;
}
