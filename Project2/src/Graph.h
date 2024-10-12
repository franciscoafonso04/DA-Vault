// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH


#include <iostream>
#include <queue>
#include <climits>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include "MutablePriorityQueue.h"


class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

/**
 * @brief Class that represents a location in the form of vertex.
 */

class Vertex {
public:

    Vertex(double in, double longitude = 0.0, double latitude = 0.0);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    double getInfo() const;
    double getLon() const;
    double getLat() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setInfo(double info);
    void setVisited(bool visited);

    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    Edge* findEdge(const double &destInfo);
    bool removeEdge(double in);
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;
protected:

    /** @brief vertex's info in double format. */
    double info;

    /** @brief vertex's longitude in double format. */
    double longitude;

    /** @brief vertex's latitude in double format. */
    double latitude;

    /** @brief outgoing edges from vertex. */
    std::vector<Edge*> adj;

    /** @brief bool visited used by DFS, BFS, Prim... */
    bool visited = false;

    /** @brief number of incoming pipes of a vertex in unsigned int format. */
    unsigned int indegree;

    /** @brief smallest distance between a source vertex and a sink vertex in double format. */
    double dist = 0;

    /** @brief vertex path in the form of edge. */
    Edge *path = nullptr;

    /** @brief vertex of all incoming edges of a location. */
    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

/**
 * @brief Class that represents a path between two locations in the form of edge.
 */

class Edge {
public:

    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    bool isVisited() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setVisited(bool visited);
protected:

    /** @brief edge's destination vertex. */
    Vertex * dest;

    /** @brief edge's capacity in double format. */
    double weight; // edge weight, can also be used for capacity

    /** @brief edge's origin location. */
    Vertex *orig;

    /** @brief edge pointer used for bidirectional edges. */
    Edge *reverse = nullptr;

    /** @brief bool visited */
    bool visited = false;

};

/********************** Graph  ****************************/

/**
 * @brief Class that represents the graph with all the vertices and edges.
 */

class Graph {
public:

    mutable std::unordered_map<size_t, Vertex*> tsp_hash;

    ~Graph();

    Vertex *findVertex(const double &in) const;
    Edge *findEdge(const double &v, const double &u) const;

    bool addVertex(Vertex* v);
    bool removeVertex(const double &in);

    bool addEdge(const double &sourc, const double &dest, double w);
    bool removeEdge(const double &source, const double &dest);
    bool addBidirectionalEdge(const double &sourc, const double &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

    std:: vector<Vertex*> dfs() const;
    std:: vector<Vertex*> dfs(const double & source) const;
    void dfsVisit(Vertex *v,  std::vector<Vertex*> & res) const;
    std::vector<double> bfs(const double & source) const;

    void removeEdges();
    void resetGraph();

protected:

    /** @brief graph's vertices vector. */
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const double &in) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

/** @brief struct that saves the results of the TSP tour. */

struct TourResult {

    /** @brief vector of vertices representing the path of the tour. */
    std::vector<Vertex*> tour;

    /** @brief total weight of the tour. */
    double totalDistance;

};

double haversine(Vertex* orig, Vertex* dest);
double euclideanDistance(Vertex* a, Vertex* b);

#endif /* DA_TP_CLASSES_GRAPH */