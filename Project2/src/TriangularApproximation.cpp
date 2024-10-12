#include "TriangularApproximation.h"

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that calculates the MST using Prim's Algorithm.
 * @details Time Complexity: O((V+E) * log(V)).
 * @param graph Pointer to the main graph.
 * @return the vertices ordered in a vector in the MST order.
 * */
vector<Vertex*> prim(Graph* graph) {
    MutablePriorityQueue<Vertex> q;

    graph->resetGraph();

    Vertex* startVertex = graph->findVertex(0);
    startVertex->setDist(0);
    q.insert(startVertex);

    while (!q.empty()) {
        Vertex *v = q.extractMin();
        if (!v->isVisited()) {
            v->setVisited(true);

            for (Edge *edge: v->getAdj()) {
                Vertex *w = edge->getDest();
                if (!w->isVisited() && edge->getWeight() < w->getDist()) {
                    w->setDist(edge->getWeight());
                    w->setPath(edge);
                    q.insert(w);
                }
            }
        }
    }

    //novo grafo (o objetivo é representar o MST)
    auto MST = new Graph();

    //adicionar os vértices
    for(auto v: graph->getVertexSet()) {
        if(v->getLat() == 0.0)
            MST->addVertex(new Vertex(v->getInfo()));
        else
            MST->addVertex(new Vertex(v->getInfo(), v->getLon(), v->getLat()));
    }

    //adicionar apenas as edges relevantes (o weight é irrelevante)
    for(auto v: graph->getVertexSet()) {
        if(v->getPath() != nullptr){
            double source = v->getPath()->getOrig()->getInfo();
            double dest = v->getInfo();
            MST->addEdge(source, dest, 0.0);
        }
    }

    //vetor com os vertices pela ordem de uma dfs search
    auto order = MST->dfs();

    //adicionar o vértice inicial mais uma vez para fazer o loop do TSP
    order.push_back(MST->findVertex(0.0));

    //calcular as distâncias para o vértice seguinte
    for(auto v = 0; v < order.size()-1; v++) {
        auto edge = graph->findVertex(order[v]->getInfo())->findEdge(order[v+1]->getInfo());
        double distance;

        if (edge == nullptr) {
            distance = haversine(order[v], order[v+1]);
            if(distance == 0.0 and order[v]->getLat() == 0.0)
                return {};
        }
        else distance = edge->getWeight();

        order[v]->setDist(distance);
    }

    graph->resetGraph();

    //retornar a ordem do caminho
    return order;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds a solution to the TSP using the triangular approximation algorithm.
 * @details Time Complexity: O((V + E) * log(V)).
 * @param graph Pointer to the graph.
 * @return TourResult containing the best tour found and its total distance.
 * */

TourResult triangularApproximation(Graph* graph){
    TourResult result;
    auto order = prim(graph);
    if (order.empty()) return result;
    result.totalDistance = 0.0;

    for(auto v = 0; v < order.size()-1; v++){
        double distance = order[v]->getDist();

        result.totalDistance += distance;
    }

    result.tour = order;
    return result;

}
