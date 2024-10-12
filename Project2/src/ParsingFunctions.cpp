#include "ParsingFunctions.h"

using namespace std;
/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reads a file from the ToyGraphs, adds the vertices to a set of all nodes, and to the graph along with the edges that connect the nodes.
 * @details Time Complexity: O(E).
 * @param graph Pointer to the main graph.
 * @param nodes Set of all the vertices and their information.
 * @param file name of the file in string format.
 * */

void read_from_toyGraph(Graph* graph, set<Vertex*>* nodes, string file) {
    ifstream csvFile;

    csvFile.open("../data/toy_graphs/" + file);

    string line;
    getline(csvFile, line);

    string ids, longitudes, latitudes;
    string id1, id2, dist, label1, label2;
    while(getline(csvFile, line)) {

        istringstream iss(line);
        getline(iss, id1, ',');
        getline(iss, id2, ',');
        getline(iss, dist, ',');
        if(file == "tourism.csv") {
            getline(iss, label1, ',');
            getline(iss, label2, ',');
        }

        auto v1 = new Vertex(stod(id1), 0, 0);
        graph->addVertex(v1);
        nodes->insert(v1);
        auto v2 = new Vertex(stod(id2), 0, 0);
        graph->addVertex(v2);
        nodes->insert(v2);

        graph->addBidirectionalEdge(v1->getInfo(), v2->getInfo(), stod(dist));
    }

    csvFile.close();
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reads a file from the FullyConnectedGraphs, adds the vertices to a set of all nodes, and to the graph along with the edges that connect the nodes.
 * @details Time Complexity: O(V + E).
 * @param graph Pointer to the main graph.
 * @param nodes Set of all the vertices and their information.
 * @param file name of the file in string format.
 * */

void read_from_fullyConnectedGraph(Graph* graph, set<Vertex*>* nodes, string file) {
    int n = check_vertices("fully-connected-graphs/" + file);
    if (n != 0) {
        read_from_nodes_fully_connected(graph, nodes, "fully-connected-graphs/nodes.csv", n);
        read_from_edges(graph, "fully-connected-graphs/" + file);
    }
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that returns the number of vertices that have edges connecting them in the file given.
 * @details Time Complexity: O(V).
 * @param path file path in string format
 * @return Number of vertices treated in the file.
 * */

int check_vertices(string path) {
    ifstream edges_;

    edges_.open("../data/" + path);

    string line;
    getline(edges_, line);


    string origins, dests, weights;
    double origin;
    int s = 1;

    while(getline(edges_, line)) {
        istringstream iss(line);
        getline(iss, origins, ',');
        getline(iss, dests, ',');
        getline(iss, weights, ',');
        origin = stod(origins);
        s++;
        if (origin != 0) return s;
    }

    edges_.close();
    return 0;
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that adds the vertices from the fully connected graphs files to the graph and to a set of vertices.
 * @details Time Complexity: O(V).
 * @param graph Pointer to the main graph.
 * @param nodes Set of all vertices and their information
 * @param path file path in string format
 * @param n number of vertices to be added.
 * */

void read_from_nodes_fully_connected(Graph* graph, set<Vertex*>* nodes, string path, int n) {
    ifstream nodes_;

    nodes_.open("../data/" + path);

    string line;
    getline(nodes_, line);

    string ids, longitudes, latitudes;
    double id, longitude, latitude;
    while(getline(nodes_, line) && n > 0) {

        istringstream iss(line);
        getline(iss, ids, ',');
        getline(iss, longitudes, ',');
        getline(iss, latitudes, ',');
        id = stod(ids);
        longitude = stod(longitudes);
        latitude = stod(latitudes);

        auto v = new Vertex(id, longitude, latitude);
        graph->addVertex(v);
        nodes->insert(v);
        n--;
    }

    nodes_.close();
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reads the files from a folder of the RealWorldGraphs, adds the vertices to a set of all nodes, and to the graph along with the edges that connect the nodes.
 * @details Time Complexity: O(V+E).
 * @param graph Pointer to the main graph.
 * @param nodes Set of all the vertices and their information.
 * @param folder name of the folder in string format.
 * */

void read_from_realGraph(Graph* graph, set<Vertex*>* nodes, string folder) {
    read_from_nodes_real(graph, nodes, "real-world-graphs/" + folder + "/nodes.csv");
    read_from_edges(graph, "real-world-graphs/" + folder + "/edges.csv");
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that adds the vertices from the real world graphs files to the graph and to a set of vertices.
 * @details Time Complexity: O(V).
 * @param graph Pointer to the main graph.
 * @param nodes Set of all vertices and their information
 * @param path file path in string format.
 * */

void read_from_nodes_real(Graph* graph, set<Vertex*>* nodes, string path) {
    ifstream nodes_;

    nodes_.open("../data/" + path);

    string line;
    getline(nodes_, line);

    string ids, longitudes, latitudes;
    double id, longitude, latitude;
    while(getline(nodes_, line)) {
        istringstream iss(line);
        getline(iss, ids, ',');
        getline(iss, longitudes, ',');
        getline(iss, latitudes, ',');
        id = stod(ids);
        longitude = stod(longitudes);
        latitude = stod(latitudes);

        auto v = new Vertex(id, longitude, latitude);
        graph->addVertex(v);
        nodes->insert(v);
    }

    nodes_.close();
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that adds the vertices connecting edges to the graph.
 * @details Time Complexity: O(E).
 * @param graph Pointer to the main graph.
 * @param path file path in string format.
 * */

void read_from_edges(Graph* graph, string path) {
    ifstream edges_;

    edges_.open("../data/" + path);

    string line;
    getline(edges_, line);


    string origins, dests, weights;
    double origin, dest, weight;

    while(getline(edges_, line)) {
        istringstream iss(line);
        getline(iss, origins, ',');
        getline(iss, dests, ',');
        getline(iss, weights, ',');
        origin = stod(origins);
        dest = stod(dests);
        weight = stod(weights);

        graph->addBidirectionalEdge(origin, dest, weight);
    }

    edges_.close();
}