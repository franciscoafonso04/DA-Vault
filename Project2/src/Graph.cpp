#include "Graph.h"
#include <iostream>

using namespace std;

/************************* Vertex  **************************/

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Constructor of vertex with arguments given by user.
 * @details Time Complexity: O(1).
 * */

Vertex::Vertex(double in, double longitude, double latitude): info(in), longitude(longitude), latitude(latitude) {}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Creates and adds edge to the graph from source (this) to dest (d) with weight w.
 *  @details Time Complexity: O(1).
 *  @param d destination vertex's code in string format.
 *  @param w in double format.
 *  @return pointer to the new edge.
 *  */

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that removes an edge from source vertex to destination vertex with info in.
 * @details Time Complexity: O(E^2).
 * @param in destination vertex's code in double format.
 * @return true if successful, and false if edge was not removed.
 * */

bool Vertex::removeEdge(double in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that removes all outgoing edges from this vertex.
 * @details Time Complexity: O(E).
 * */

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the info of a vertex of the graph.
 * @details Time Complexity: O(1).
 * @return info in double format.
 * */

double Vertex::getInfo() const {
    return this->info;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the longitude of a vertex of the graph.
 * @details Time Complexity: O(1).
 * @return longitude in double format.
 * */

double Vertex::getLon() const {
    return this->longitude;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the latitude of a vertex of the graph.
 * @details Time Complexity: O(1).
 * @return latitude in double format.
 * */

double Vertex::getLat() const {
    return this->latitude;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vector of outgoing edges of a vertex.
 * @details Time Complexity: O(1).
 * @return adj represented as a vector of pointers to edges.
 * */

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex's visited value.
 * @details Time Complexity: O(1).
 * @return visited in bool format.
 * */

bool Vertex::isVisited() const {
    return this->visited;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex's number of incoming edges.
 * @details Time Complexity: O(1).
 * @return indegree in unsigned int format.
 * */

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex's dist.
 * @details Time Complexity: O(1).
 * @return dist in double format.
 * */

double Vertex::getDist() const {
    return this->dist;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex's path.
 * @details Time Complexity: O(1).
 * @return path in Edge format.
 * */

Edge *Vertex::getPath() const {
    return this->path;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex's incoming edges.
 * @details Time Complexity: O(1).
 * @return incoming in the format of vector of pointers of edges.
 * */

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex's info value.
 * @details Time Complexity: O(1).
 * @param in in double format.
 * */

void Vertex::setInfo(double in) {
    this->info = in;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex's visited value.
 * @details Time Complexity: O(1).
 * @param visited in bool format.
 * */

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex's indegree value.
 * @details Time Complexity: O(1).
 * @param indegree in unsigned int format.
 * */

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex's dist value.
 * @details Time Complexity: O(1).
 * @param dist in double format.
 * */

void Vertex::setDist(double dist) {
    this->dist = dist;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex's path value.
 * @details Time Complexity: O(1).
 * @param path in pointer of edge format.
 * */

void Vertex::setPath(Edge *path) {
    this->path = path;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that deletes edge from graph.
 * @details Time Complexity: O(E).
 * @param edge in pointer of edge format.
 * */

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Constructor of edge with arguments given by user.
 * @details Time Complexity: O(1).
 * */

Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge's destination vertex.
 * @details Time Complexity: O(1).
 * @return dest represented as a pointer of a vertex.
 * */

Vertex * Edge::getDest() const {
    return this->dest;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge's weight.
 * @details Time Complexity: O(1).
 * @return weight in double format.
 * */

double Edge::getWeight() const {
    return this->weight;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge's origin vertex.
 * @details Time Complexity: O(1).
 * @return orig represented as a pointer of a vertex.
 * */

Vertex * Edge::getOrig() const {
    return this->orig;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the edge's reverse edge.
 * @details Time Complexity: O(1).
 * @param reverse represented as a pointer of an edge.
 * */

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds an edge from this vertex to a dest vertex with destInfo.
 * @details Time Complexity: O(E).
 * @param destInfo dest vertex's info in double format.
 * @return a pointer of the edge that connects this vertex and dest vertex.
 * */

Edge* Vertex::findEdge(const double &destInfo) {
    for (auto edge : adj) {
        if (edge->getDest()->getInfo() == destInfo) {
            return edge;
        }
    }
    return nullptr;  // Return nullptr if no edge found
}

/********************** Graph  ****************************/

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the number of vertices of the graph.
 * @details Time Complexity: O(1).
 * @return vertexSet size in int format.
 * */

int Graph::getNumVertex() const {
    return vertexSet.size();
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertices of the graph.
 * @details Time Complexity: O(1).
 * @return vertexSet represented as a vector of pointers of vertices.
 * */

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that returns a pointer to the vertex with the same code as the double in, using hash.
 * @details Time Complexity: O(1).
 * @param in Given vertex's code in double format.
 * @return pointer to the vertex with the same code as the double in.
 * */

Vertex * Graph::findVertex(const double &in) const {
    size_t hash = std::hash<double>{}(in);

    auto it = tsp_hash.find(hash);

    if (it != tsp_hash.end()) {
        // Found in the hash map, return the vertex pointer
        return it->second;
    } else {
        // If not found, iterate through the graph to find the vertex
        for (auto v: vertexSet) {
            if (v->getInfo() == in) {
                // Store the vertex pointer in the hash map for future searches
                tsp_hash.emplace(hash, v);
                return v;
            }
        }
    }
    return nullptr;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that returns a pointer to the edge that connects the origin vertex with info v and the destination vertex with info u.
 * @details Time Complexity: O(E).
 * @param v Origin vertex's info double format.
 * @param u Destination vertex's info in double format.
 * @return pointer to the edge that connects the vertices.
 * */

Edge* Graph::findEdge(const double &v, const double &u) const {
    auto orig = findVertex(v);
    for(auto e: orig->getAdj())
        if(e->getDest()->getInfo() == u)
            return e;
    return nullptr;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that returns the index of the vertex with the same code as the double in.
 * @details Time Complexity: O(V).
 * @param in Given vertex's code in string format.
 * @return index of the vertex.
 * */

int Graph::findVertexIdx(const double &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Adds a vertex to the graph.
 *  @details Time Complexity: O(1).
 *  @param v Given vertex.
 *  @return true if successful, and false if the vertex is already in the vertexSet.
 *  */

bool Graph::addVertex(Vertex *v) {
    if (findVertex(v->getInfo()) != nullptr)
        return false;
    vertexSet.push_back(v);
    return true;
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Removes a vertex to the graph and all its outgoing and incoming edges.
 *  @details Time Complexity: O(V * E^2).
 *  @param in Given vertex's info in double format.
 *  @return true if successful, and false if the vertex does not exist.
 *  */

bool Graph::removeVertex(const double &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            vertexSet.erase(it);
            return true;
        }
    }
    return false;
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Adds an edge to the graph from vertex sourc to vertex dest with weight w.
 *  @details Time Complexity: O(1).
 *  @param sourc source vertex's info in double format.
 *  @param dest destination vertex's info in double format.
 *  @param w in double format.
 *  @return true if successful, and false if the vertices do not exist.
 *  */

bool Graph::addEdge(const double &sourc, const double &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Removes an edge of the graph from vertex sourc to vertex dest with weight w.
 *  @details Time Complexity: O(E).
 *  @param sourc source vertex's info in double format.
 *  @param dest destination vertex's info in double format.
 *  @return true if successful, and false if the edge does not exist.
 *  */

bool Graph::removeEdge(const double &sourc, const double &dest) {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Adds a bidirectional edge to the graph from vertex sourc to vertex dest with weight w.
 *  @details Time Complexity: O(1).
 *  @param sourc source vertex's info in double format.
 *  @param dest destination vertex's info in double format.
 *  @param w in double format.
 *  @return true if successful, and false if the vertices do not exist.
 *  */

bool Graph::addBidirectionalEdge(const double &sourc, const double &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs a depth-first search (dfs) traversal in the graph.
 * @details Time Complexity: O(V+E).
 * @return a vector with the vertices.
 * */

std::vector<Vertex*> Graph::dfs() const {
    std::vector<Vertex*> res;
    for (auto v : vertexSet)
        v->setVisited(false);
    for (auto v : vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs a depth-first search (dfs) traversal in the graph from the source vertex.
 * @details Time Complexity: O(V+E).
 * @param source vertex's info in double format.
 * @return a vector with the vertices.
 * */

std::vector<Vertex*> Graph::dfs(const double & source) const {
    std::vector<Vertex*> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }
    // Perform the actual DFS using recursion
    dfsVisit(s, res);

    return res;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that visits an vertex (v) and its adjacent, recursively, and updates the vector of vertices.
 * @details Time Complexity: O(E).
 * @param v Pointer to the vertex to visit.
 * @param res vector with the vertices.
 * */

void Graph::dfsVisit(Vertex *v, std::vector<Vertex*> & res) const {
    v->setVisited(true);
    res.push_back(v);
    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs a breadth-first search (bfs) in the graph starting from the vertex with the code source.
 * @details Time Complexity: O(V + E).
 * @param source code of source vertex in double format.
 * @return a vector with the contents of the vertices by bfs order.
 * */

std::vector<double> Graph::bfs(const double & source) const {
    std::vector<double> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }

    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v->setVisited(false);
    }

    // Perform the actual BFS using a queue
    std::queue<Vertex *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for (auto & e : v->getAdj()) {
            auto w = e->getDest();
            if ( ! w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}


Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}


void Graph::resetGraph() {
    for (Vertex* v : vertexSet) {
        v->setVisited(false);
        v->setDist(INF);
        v->setPath(nullptr);
    }
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that calculates the distance between two vertices by using the Haversine Formula.
 * @details Time Complexity: O(1).
 * @param orig Origin Vertex.
 * @param dest Destination Vertex.
 * @return the distance of the arc between the two vertices.
 * */

double haversine(Vertex* orig, Vertex* dest) {
    double lat1 = orig->getLat();
    double lon1 = orig->getLon();
    double lat2 = dest->getLat();
    double lon2 = dest->getLon();

    double radLat1 = lat1 * M_PI / 180.0;
    double radLon1 = lon1 * M_PI / 180.0;
    double radLat2 = lat2 * M_PI / 180.0;
    double radLon2 = lon2 * M_PI / 180.0;

    double deltaLat = radLat2 - radLat1;
    double deltaLon = radLon2 - radLon1;

    double aux = pow(sin(deltaLat / 2), 2) + pow(sin(deltaLon / 2), 2) * cos(radLat1) * cos(radLat2);
    double c = 2.0 * atan2(sqrt(aux), sqrt(1.0 - aux));
    return 6371000.0 * c;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that calculates the euclidean distance between two vertices.
 * @details Time Complexity: O(1).
 * @param a Vertex 1.
 * @param b Vertex 2.
 * @return the direct distance between the two vertices.
 * */

double euclideanDistance(Vertex* a, Vertex* b) {
    double lon1 = a->getLon(), lat1 = a->getLat();
    double lon2 = b->getLon(), lat2 = b->getLat();
    return sqrt((lon2 - lon1) * (lon2 - lon1) + (lat2 - lat1) * (lat2 - lat1));
}