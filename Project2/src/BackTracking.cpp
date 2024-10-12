#include "BackTracking.h"


/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Utility function for TSP to explore all paths recursively.
 * @details Time complexity for this utility function depends on the number of vertices left to explore, resulting in a factorial growth, O((V - count)!).
 * @param graph Pointer to the graph being explored.
 * @param v Current vertex in the path.
 * @param currentWeight Total weight of the current path.
 * @param count Number of vertices visited so far.
 * @param minWeight Reference to store the minimum weight found.
 * @param currentPath Current path taken.
 * @param bestPath Reference to store the best path found.
 * */

void tspUtil(Graph* graph, Vertex *v, double currentWeight, int count, double &minWeight, std::vector<Vertex*>& currentPath, std::vector<Vertex*>& bestPath) {
    // Check if all vertices are visited and return to the first vertex
    currentPath.push_back(v);

    if (count == graph->getNumVertex() && v->findEdge(graph->getVertexSet().at(0)->getInfo())) {
        double totalWeight = currentWeight + v->findEdge(graph->getVertexSet().at(0)->getInfo())->getWeight();
        if (totalWeight < minWeight) {
            minWeight = totalWeight;
            bestPath = currentPath;
            bestPath.push_back(graph->getVertexSet().at(0));
        }
    } else {
        for (auto edge : v->getAdj()) {
            if (!(edge->getDest()->isVisited())) {
                edge->getDest()->setVisited(true);
                tspUtil(graph, edge->getDest(),  currentWeight + edge->getWeight(), count + 1, minWeight, currentPath, bestPath);
                edge->getDest()->setVisited(false);
            }
        }
    }

    currentPath.pop_back();
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds a solution to the TSP using the backtracking algorithm.
 * @details Time Complexity: O(V!), each vertex will be included in the path exactly once, and every permutation is explored.
 * @param graph Pointer to the graph.
 * @return TourResult containing the best tour found and its total distance.
 * */

TourResult findTSP(Graph* graph) {

    TourResult result;
    std::vector<Vertex*> bestPath;
    double minWeight = INT_MAX;
    std::vector<Vertex*> currentPath;

    // Start from the first vertex
    graph->getVertexSet().at(0)->setVisited(true);
    tspUtil(graph, graph->getVertexSet().at(0), 0, 1, minWeight, currentPath, bestPath);
    graph->getVertexSet().at(0)->setVisited(false); // Clean up visited status after search

    result.totalDistance = minWeight;
    result.tour = bestPath;
    return result;
}



