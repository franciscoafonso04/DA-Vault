#include "RealWorld.h"

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs the Prim algorithm to find the MST of the graph.
 * @details Time Complexity: O(V * E * log²(v)).
 * @param graph Pointer to the graph.
 * @param n info of the vertex where the algorithm starts.
 * @return vector of pointers of vertices that represent the result of the algorithm performed.
 * */

vector<Vertex*> prim(Graph& graph, double n) {
    MutablePriorityQueue<Vertex> q;

    graph.resetGraph();

    Vertex* startVertex = graph.findVertex(n);
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
    for(auto v: graph.getVertexSet()) {
        if(v->getLat() == 0.0) MST->addVertex(new Vertex(v->getInfo()));
        else MST->addVertex(new Vertex(v->getInfo(), v->getLon(), v->getLat()));
    }

    //adicionar apenas as edges relevantes (o weight é irrelevante)
    for(auto v: graph.getVertexSet()) {
        if(v->getPath() != nullptr){
            double source = v->getPath()->getOrig()->getInfo();
            double dest = v->getInfo();
            MST->addEdge(source, dest, 0.0);
        }
    }

    //vetor com os vertices pela ordem de uma dfs search
    auto order = MST->dfs(n);

    //calcular as distâncias para o vértice seguinte
    for(auto v = 0; v < order.size()-1; v++) {
        auto edge = graph.findVertex(order[v]->getInfo())->findEdge(order[v+1]->getInfo());
        double distance;

        if(edge == nullptr) distance = haversine(order[v], order[v+1]);
        else distance = edge->getWeight();

        order[v]->setDist(distance);
    }

    graph.resetGraph();


    //retornar a ordem do caminho
    return order;
}

/** ---------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds a solution to the TSP using the mst of the graph (based on triangular approximation) and prints the resulting tour as well as it's total distance.
 * @details Time Complexity: O(V * E * log²(v)).
 * @param graph Pointer to the graph.
 * @param n info of the vertex where the algorithm starts.
 * */

void realWorld(Graph &graph, double firstVertex) {
    TourResult result;
    vector<Vertex *> vertexSet = graph.getVertexSet();

    result.tour = prim(graph, firstVertex);

    bool exists = false;
    Vertex *last = graph.findVertex(result.tour.back()->getInfo());
    for (auto e: last->getAdj()) {
        if (e->getDest()->getInfo() == firstVertex) {
            exists = true;
            result.tour.push_back(e->getDest());
            result.totalDistance += e->getWeight();
            break;
        }
    }

    if (!exists) {
        result.totalDistance = 0;
        cout << "There is no feasible path" << endl;
        return;
    }

    double distanceSum = 0;
    for (int i = 0; i < result.tour.size() - 1; i++) {
        cout << result.tour[i]->getInfo() << /*" - " << distance << */" -> ";

        double distance = result.tour[i]->getDist();
        distanceSum += distance;
    }
    cout << result.tour.back()->getInfo() << endl;
    cout << "Total distance covered: " << distanceSum << endl;
}
