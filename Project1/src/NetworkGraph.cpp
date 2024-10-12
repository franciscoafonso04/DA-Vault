#include "NetworkGraph.h"

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Constructor of city with arguments given by user.
 * @details Time Complexity: O(1).
 * */

Vertex::Vertex(string city_, int id_, char type_, string code_, double demand_, double population_): name(city_), id(id_), type(type_), code(code_), demand(demand_), population(population_) {}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Constructor of reservoir with arguments given by user.
 * @details Time Complexity: O(1).
 * */

Vertex::Vertex(string reservoir_, char type_, string mun_, int id_, string code_, double maxDel_): name(reservoir_), type(type_),  mun(mun_), id(id_), code(code_), maxDel(maxDel_) {}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Constructor of pumping station with arguments given by user.
 * @details Time Complexity: O(1).
 * */

Vertex::Vertex(int id_, string code_, char type_): id(id_), code(code_), type(type_) {}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Creates and adds edge/pipe to the graph/network from source (this) to dest (d) with weight w.
 *  @details Time Complexity: O(1).
 *  @param d destination vertex/location's code in string format.
 *  @param w in double format.
 *  @return pointer to the new edge/pipe.
 *  */

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that removes an edge from source vertex/location (this) to destination vertex/location with code code_.
 * @details Time Complexity: O(E^2).
 * @param code_ destination vertex/location's code in string format.
 * @return true if successful, and false if edge was not removed.
 * */

bool Vertex::removeEdge(string code_) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getCode() == code_) {
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

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that removes all outgoing edges/pipes from this vertex/location.
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
 * @brief Getter of the code of a vertex/location of the graph/network.
 * @details Time Complexity: O(1).
 * @return code in string format.
 * */

string Vertex::getCode() const {
    return this->code;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the type of a vertex/location of the graph/network.
 * @details Time Complexity: O(1).
 * @return type in char format.
 * */

char Vertex::getType() const {
    return this->type;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the id of a vertex/location of the graph/network.
 * @details Time Complexity: O(1).
 * @return id in int format.
 * */

int Vertex::getId() const{
    return this->id;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the name of a vertex/location of the graph/network.
 * @details Time Complexity: O(1).
 * @return name in string format.
 * */

string Vertex::getName() const{
    return this->name;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the municipality of a reservoir of the graph/network.
 * @details Time Complexity: O(1).
 * @return municipality in string format.
 * */

string Vertex::getMun() const{
    return this->mun;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the maximum delivery of a reservoir of the graph/network.
 * @details Time Complexity: O(1).
 * @return maxDelivery in double format.
 * */

double Vertex::getMaxDel() const{
    return this->maxDel;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the demand of a city of the graph/network.
 * @details Time Complexity: O(1).
 * @return demand in double format.
 * */

double Vertex::getDemand() const{
    return this->demand;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the population of a city of the graph/network.
 * @details Time Complexity: O(1).
 * @return population in double format.
 * */

double Vertex::getPopulation() const{
    return this->population;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vector of outgoing edges/pipes of a vertex/location.
 * @details Time Complexity: O(1).
 * @return adj represented as a vector of pointers to edges/pipes.
 * */

vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex/location's visited value.
 * @details Time Complexity: O(1).
 * @return visited in bool format.
 * */

bool Vertex::isVisited() const {
    return this->visited;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex/location's processing value.
 * @details Time Complexity: O(1).
 * @return processing in bool format.
 * */

bool Vertex::isProcessing() const {
    return this->processing;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex/location's number of incoming edges/pipes.
 * @details Time Complexity: O(1).
 * @return indegree in unsigned int format.
 * */

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex/location's dist.
 * @details Time Complexity: O(1).
 * @return dist in double format.
 * */

double Vertex::getDist() const {
    return this->dist;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex/location's path.
 * @details Time Complexity: O(1).
 * @return path in Edge format.
 * */

Edge *Vertex::getPath() const {
    return this->path;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertex/location's incoming edges/pipes.
 * @details Time Complexity: O(1).
 * @return incoming in the format of vector of pointers of edges.
 * */

vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex/location's code value.
 * @details Time Complexity: O(1).
 * @param in in string format.
 * */

void Vertex::setCode(string in) {
    this->code = in;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex/location's visited value.
 * @details Time Complexity: O(1).
 * @param visited in bool format.
 * */

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex/location's processing value.
 * @details Time Complexity: O(1).
 * @param processing in bool format.
 * */

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex/location's indegree value.
 * @details Time Complexity: O(1).
 * @param indegree in unsigned int format.
 * */

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex/location's dist value.
 * @details Time Complexity: O(1).
 * @param dist in double format.
 * */

void Vertex::setDist(double dist) {
    this->dist = dist;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the vertex/location's path value.
 * @details Time Complexity: O(1).
 * @param path in pointer of edge format.
 * */

void Vertex::setPath(Edge *path) {
    this->path = path;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that deletes edge/pipe from graph/network.
 * @details Time Complexity: O(E).
 * @param edge in pointer of edge format.
 * */

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getCode() == code) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}


/****************************************************************************************************************************/
/******************************************************** Edge **************************************************************/
/****************************************************************************************************************************/


/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Constructor of edge/pipe with arguments given by user.
 * @details Time Complexity: O(1).
 * */

Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w), weight_aux(w) {}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge/pipe's origin vertex.
 * @details Time Complexity: O(1).
 * @return orig represented as a pointer of a vertex.
 * */

Vertex * Edge::getOrig() const {
    return this->orig;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge/pipe's destination vertex.
 * @details Time Complexity: O(1).
 * @return dest represented as a pointer of a vertex.
 * */

Vertex * Edge::getDest() const {
    return this->dest;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge/pipe's weight.
 * @details Time Complexity: O(1).
 * @return weight in double format.
 * */

double Edge::getWeight() const {
    return this->weight;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge/pipe's auxiliary weight.
 * @details Time Complexity: O(1).
 * @return auxiliary weight in double format.
 * */

double Edge::getWeightAux() const {
    return this->weight_aux;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge/pipe's reverse edge.
 * @details Time Complexity: O(1).
 * @return reverse represented as a pointer of an edge.
 * */

Edge *Edge::getReverse() const {
    return this->reverse;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the edge/pipe's flow.
 * @details Time Complexity: O(1).
 * @return flow in double format.
 * */

double Edge::getFlow() const {
    return flow;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the edge/pipe's reverse edge.
 * @details Time Complexity: O(1).
 * @param reverse represented as a pointer of an edge.
 * */

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the edge/pipe's flow.
 * @details Time Complexity: O(1).
 * @param flow in double format.
 * */

void Edge::setFlow(double flow) {
    this->flow = flow;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Setter of the edge/pipe's weight.
 * @details Time Complexity: O(1).
 * @param weight in double format.
 * */

void Edge::setWeight(double weight) {
    this->weight = weight;
}

/***************************************************************************************************************************/
/******************************************************* Graph *************************************************************/
/***************************************************************************************************************************/

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the number of vertices/locations of the graph/network.
 * @details Time Complexity: O(1).
 * @return vertexSet size in int format.
 * */

int NetworkGraph::getNumVertex() const {
    return vertexSet.size();
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Getter of the vertices/locations of the graph/network.
 * @details Time Complexity: O(1).
 * @return vertexSet represented as a vector of pointers of vertices.
 * */

vector<Vertex *> NetworkGraph::getVertexSet() const {
    return vertexSet;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that returns a pointer to the vertex/location with the same code as the string in, using hash.
 * @details Time Complexity: O(1).
 * @param in Given vertex/location's code in string format.
 * @return pointer to the vertex/location with the same code as the string in.
 * */

Vertex * NetworkGraph::findVertex(const string &in) const {
    size_t hash = ::hash<string>{}(in);

    auto it = network_hash.find(hash);

    if (it != network_hash.end()) {
        // Found in the hash map, return the vertex pointer
        return it->second;
    } else {
        // If not found, iterate through the graph to find the vertex
        for (auto v: vertexSet) {
            if (v->getCode() == in) {
                // Store the vertex pointer in the hash map for future searches
                network_hash.emplace(hash, v);
                return v;
            }
        }
    }
    return nullptr;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that returns a pointer to the edge/pipe from vertex/location sourc to vertex/location dest.
 * @details Time Complexity: O(V + E).
 * @param sourc Reference of source vertex/location.
 * @param dest Reference of destination vertex/location.
 * @return the pointer to the found edge, a null pointer otherwise
 * */

Edge* NetworkGraph::findEdge(const string &sourc, const string &dest){
    Vertex* v1;
    bool real;

    for(auto v: vertexSet)
        if(v->getCode() == sourc) {
            v1 = v;
            real = true;
        }

    if(real)
        for(auto e: v1->getAdj())
            if(e->getDest()->getCode() == dest) return e;

    return nullptr;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that returns the index of the vertex/location with the same code as the string in.
 * @details Time Complexity: O(V).
 * @param in Given vertex/location's code in string format.
 * @return index of the vertex/location.
 * */

int NetworkGraph::findVertexIdx(const string &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getCode() == in)
            return i;
    return -1;
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Adds a vertex/location to the graph/network.
 *  @details Time Complexity: O(1).
 *  @param v Given vertex/location.
 *  @return true if successful, and false if the vertex/location is already in the vertexSet.
 *  */

bool NetworkGraph::addVertex(Vertex *v) {
    if (findVertex(v->getCode()) != nullptr)
        return false;
    vertexSet.push_back(v);
    return true;
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Removes a vertex/location to the graph/network and all its outgoing and incoming edges/pipes.
 *  @details Time Complexity: O(V * E^2).
 *  @param in Given vertex/location's code in string format.
 *  @return true if successful, and false if the vertex/location does not exist.
 *  */

bool NetworkGraph::removeVertex(const string &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getCode() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getCode());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Adds an edge/pipe to the graph/network from vertex/location sourc to vertex/location dest with weight w.
 *  @details Time Complexity: O(1).
 *  @param sourc source vertex/location's code in string format.
 *  @param dest destination vertex/location's code in string format.
 *  @param w in double format.
 *  @return true if successful, and false if the vertices/locations do not exist.
 *  */

bool NetworkGraph::addEdge(const string &sourc, const string &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}


/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Removes an edge/pipe of the graph/network from vertex/location sourc to vertex/location dest with weight w.
 *  @details Time Complexity: O(E).
 *  @param sourc source vertex/location's code in string format.
 *  @param dest destination vertex/location's code in string format.
 *  @return true if successful, and false if the edge/pipe does not exist.
 *  */

bool NetworkGraph::removeEdge(const string &sourc, const string &dest) {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

/** -------------------------------------------------------------------------------------------------------------------------
 *  @brief Adds a bidirectional edge/pipe to the graph/network from vertex/location sourc to vertex/location dest with weight w.
 *  @details Time Complexity: O(1).
 *  @param sourc source vertex/location's code in string format.
 *  @param dest destination vertex/location's code in string format.
 *  @param w in double format.
 *  @return true if successful, and false if the vertices/locations do not exist.
 *  */

bool NetworkGraph::addBidirectionalEdge(const string &sourc, const string &dest, double w) {
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
 * @brief Function that performs a depth-first search (dfs) traversal in the graph/network.
 * @details Time Complexity: O(V+E).
 * @return a vector with the codes of the vertices/locations.
 * */

vector<string> NetworkGraph::dfs() const {
    vector<string> res;
    for (auto v : vertexSet)
        v->setVisited(false);
    for (auto v : vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs a depth-first search (dfs) traversal in the graph/network from the source vertex/location.
 * @details Time Complexity: O(V+E).
 * @param source vertex/location's code in string format.
 * @return a vector with the codes of the vertices/locations.
 * */

vector<string> NetworkGraph::dfs(const string & source) const {
    vector<string> res;
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
 * @brief Function that visits an vertex/location (v) and its adjacent, recursively, and updates the vector of strings.
 * @details Time Complexity: O(E).
 * @param v Pointer to the vertex/location to visit.
 * @param res vector with the contents of the airports/vertices.
 * */

void NetworkGraph::dfsVisit(Vertex *v, vector<string> & res) const {
    v->setVisited(true);
    res.push_back(v->getCode());
    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs a breadth-first search (bfs) in the graph starting from the vertex/location with the code source.
 * @details Time Complexity: O(V + E).
 * @param source code of source vertex/location in string format.
 * @return a vector with the contents of the vertices/locations by bfs order.
 * */

vector<string> NetworkGraph::bfs(const string & source) const {
    vector<string> res;
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
    queue<Vertex *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getCode());
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

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs a depth-first search in a graph, to determine if the graph is acyclic (acyclic directed graph or DAG).
 * @details Time Complexity: O(V*E).
 * @return true if the graph is acyclic, and false otherwise.
 * */

bool NetworkGraph::isDAG() const {
    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setProcesssing(false);
    }
    for (auto v : vertexSet) {
        if (! v->isVisited()) {
            if ( ! dfsIsDAG(v) ) return false;
        }
    }
    return true;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * @details Time Complexity: O(E).
 * @param v vertex/location to be visited.
 * @return false (not acyclic) if an edge/pipe to a vertex/location in the stack is found.
 * */

bool NetworkGraph::dfsIsDAG(Vertex *v) const {
    v->setVisited(true);
    v->setProcesssing(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (w->isProcessing()) return false;
        if (! w->isVisited()) {
            if (! dfsIsDAG(w)) return false;
        }
    }
    v->setProcesssing(false);
    return true;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that performs a topological sorting of the vertices/locations of the graph/network.
 * @details Time Complexity: O(V + E).
 * @return false (not acyclic) if an edge to a vertex in the stack is found.
 * */

vector<string> NetworkGraph::topsort() const {
    vector<string> res;

    for (auto v : vertexSet) {
        v->setIndegree(0);
    }
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    queue<Vertex *> q;
    for (auto v : vertexSet) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while( !q.empty() ) {
        Vertex * v = q.front();
        q.pop();
        res.push_back(v->getCode());
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if(w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if ( res.size() != vertexSet.size() ) {
        //cout << "Impossible topological ordering!" << endl;
        res.clear();
        return res;
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

NetworkGraph::~NetworkGraph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}
