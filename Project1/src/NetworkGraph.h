#ifndef PROJETO_NETWORKGRAPH_H
#define PROJETO_NETWORKGRAPH_H

#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Edge;

#define INF numeric_limits<double>::max()

/************************* Vertex  **************************/

/**
 * @brief Class that represents a location (Reservoir/Pumping Station/City) in the form of vertex.
 */

class Vertex {
public:

    Vertex(string city_, int id_, char type_, string code_, double demand_, double population_); // city constructor
    Vertex(string reservoir_, char type_, string mun_, int id_, string code_, double maxDel_); // reservoir constructor
    Vertex(int id_, string code_, char type_); // station constructor

    bool operator< (Vertex & vertex) const; // // required by MutablePriorityQueue

    string getCode() const;
    char getType() const;
    int getId() const;
    string getName() const;
    string getMun() const;
    double getMaxDel() const;
    double getDemand() const;
    double getPopulation() const;
    vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    vector<Edge *> getIncoming() const;

    void setCode(string code);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(string in);
    void removeOutgoingEdges();

protected:

    /** @brief location code in string format. */
    string code;

    /** @brief location type in char format (C , P or R). */
    char type;

    /** @brief id in int format. */
    int id;

    /** @brief location name in string format. */
    string name;

    /** @brief city's population in double format. */
    double population;

    /** @brief city's demand in double format. */
    double demand;

    /** @brief reservoir's max delivery in double format. */
    double maxDel;

    /** @brief reservoir's municipality in string format. */
    string mun;

    /** @brief outgoing pipes from location. */
    vector<Edge *> adj;

    /** @brief bool visited used by DFS, BFS, Prim... */
    bool visited = false;

    /** @brief bool processing used by isDag. */
    bool processing = false; // used by isDAG (in addition to the visited attribute)

    /** @brief number of incoming pipes of a location in unsigned int format. */
    unsigned int indegree;

    /** @brief smallest distance between a source vertex and a sink vertex in double format. */
    double dist = 0;

    /** @brief vertex of all incoming pipes of a location. */
    vector<Edge *> incoming; // incoming edges

    /** @brief vertex path in the form of edge/pipe. */
    Edge *path = nullptr;

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

/**
 * @brief Class that represents a pipe in the form of edge.
 */

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    double getWeightAux() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setWeight(double weight);
protected:

    /** @brief pipe's destination vertex/location. */
    Vertex * dest;

    /** @brief pipe's capacity in double format. */
    double weight;

    /** @brief auxiliary capacity in double format. */
    double weight_aux;

    /** @brief pipe's water flow in double format. */
    double flow;

    /** @brief pipe's origin location. */
    Vertex *orig;

    /** @brief edge pointer used for bidirectional pipes. */
    Edge *reverse = nullptr;

};

/********************** Graph  ****************************/

/**
 * @brief Class that represents the water supply network in the form of graph.
 */

class NetworkGraph {
public:
    mutable unordered_map<size_t, Vertex*> network_hash;

    ~NetworkGraph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const string &in) const;
    /*
    * Auxiliary function to find an edge with a given sorce and destination.
    */
    Edge* findEdge(const string &sourc, const string &dest);
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex( Vertex *v );
    bool removeVertex(const string &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const string &sourc, const string &dest, double w);
    bool removeEdge(const string &source, const string &dest);
    bool addBidirectionalEdge(const string &sourc, const string &dest, double w);


    int getNumVertex() const;
    vector<Vertex *> getVertexSet() const;

    vector<string> dfs() const;
    vector<string> dfs(const string & source) const;
    void dfsVisit(Vertex *v,  vector<string> & res) const;
    vector<string> bfs(const string & source) const;

    bool isDAG() const;
    bool dfsIsDAG(Vertex *v) const;
    vector<string> topsort() const;
protected:

    /** @brief graph's locations vector. */
    vector<Vertex *> vertexSet;
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
    int findVertexIdx(const string &in) const; //Finds the index of the vertex with a given content.
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


#endif //PROJETO_NETWORKGRAPH_H
