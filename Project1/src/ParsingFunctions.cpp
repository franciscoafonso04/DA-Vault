#include "ParsingFunctions.h"
using namespace std;

bool small = 0;


/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reads the "Cities.csv" file, adds the cities to the NetworkGraph and to a set of all cities and their information.
 * @details Time Complexity: O(V * log(V)).
 * @param cities Set that will contain all the cities and their information.
 * @param network Water Supply Network Graph.
 * */

void read_from_cities(set<Vertex*>& cities, NetworkGraph& network) {
    ifstream cities_;

    if(small) cities_.open("../small_data/Cities.csv");
    else cities_.open("../large_data/Cities.csv");

    string line;
    getline(cities_, line);

    string city, id, code, demand, population;

    while(getline(cities_, line)) {

        istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, ',');
        char type = code[0];

        auto v = new Vertex(city, stoi(id), type, code, stod(demand), stod(population));
        network.addVertex(v);
        cities.insert(v);

    }

    cities_.close();
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reads the "Reservoir.csv" file, adds the reservoirs to the NetworkGraph and to a set of all reservoirs and their information.
 * @details Time Complexity: O(V * log(V)).
 * @param cities Set that will contain all the reservoirs and their information.
 * @param network Water Supply Network Graph.
 * */

void read_from_reservoirs(set<Vertex*>& reservoirs, NetworkGraph& network) {
    ifstream reservoirs_;

    if(small) reservoirs_.open("../small_data/Reservoir.csv");
    else reservoirs_.open("../large_data/Reservoir.csv");

    string line;
    getline(reservoirs_, line);

    string reservoir, municipality, id, code, maxDel;

    while(getline(reservoirs_, line)) {
        istringstream iss(line);
        getline(iss, reservoir, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, maxDel, ',');

        char type = code[0];

        auto v = new Vertex(reservoir, type, municipality, stoi(id), code, stod(maxDel));

        network.addVertex(v);
        reservoirs.insert(v);
    }

    reservoirs_.close();
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reads the "Stations.csv" file, adds the pumping stations to the NetworkGraph and to a set of all pumping stations and their information.
 * @details Time Complexity: O(V * log(V)).
 * @param stations Set that will contain all the pumping stations and their information.
 * @param network Water Supply Network Graph.
 * */

void read_from_stations(set<Vertex*>& stations, NetworkGraph& network) {
    ifstream stations_;

    if(small) stations_.open("../small_data/Stations.csv");
    else stations_.open("../large_data/Stations.csv");

    string line;
    getline(stations_, line);

    string id, code;

    while(getline(stations_, line)) {
        istringstream iss(line);
        getline(iss, id, ',');
        getline(iss, code, ',');

        char type = code[0];

        auto v = new Vertex(stoi(id), code, type);

        network.addVertex(v);
        stations.insert(v);
    }

    stations_.close();
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reads the "Pipes.csv" file, adds the pipes/edges to the NetworkGraph.
 * @details Time Complexity: O(E).
 * @param network Water Supply Network Graph.
 * */

void read_from_pipes(NetworkGraph& network) {
    ifstream pipes_;

    if(small) pipes_.open("../small_data/Pipes.csv");
    else pipes_.open("../large_data/Pipes.csv");

    string line;
    getline(pipes_, line);


    string SPA, SPB, capacity, direction;

    while(getline(pipes_, line)) {

        istringstream iss(line);
        getline(iss, SPA, ',');
        getline(iss, SPB, ',');
        getline(iss, capacity, ',');
        getline(iss, direction, ',');

        if(direction == "1") {
            network.addEdge(SPA, SPB, stod(capacity));
        }
        else {
            network.addBidirectionalEdge(SPA, SPB, stod(capacity));
        }

    }

    pipes_.close();
}

/** -----------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Function that writes each city's max flow in the "Flow.csv" file.
 * @details Time Complexity: O(V).
 * @param g Water Supply Network Graph.
 * @param maxFlowMap Map that stores each city's maxFlow.
 * */

void write_max_flow(NetworkGraph *g, map<int, pair<string, double>> maxFlowMap) {
    ofstream maxFlow;
    maxFlow.open("../results/Flow.csv", std::ios::out | std::ios::trunc);

    maxFlow << "CityCode,Value" << endl;

    for(auto const city: maxFlowMap)
        maxFlow << "C_" << city.first << ',' << city.second.second << endl;

    maxFlow.close();
}
