#ifndef DOWNSTREAM_APP_H
#define DOWNSTREAM_APP_H

#include "ParsingFunctions.h"
#include <chrono>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

/**
 * @brief Class that represents the main program interface and all of its stored data.
 */

class App {

    /** @brief set of vertices that stores all cities for optimized search. */
    set<Vertex*> cities;

    /** @brief set of vertices that stores all reservoirs for optimized search. */
    set<Vertex*> reservoirs;

    /** @brief set of vertices that stores all pumping stations for optimized search. */
    set<Vertex*> stations;

    /** @brief water supply network's graph. */
    NetworkGraph network;

    /** @brief map that stores the maximum amount of water that reach each city. */
    map<int, pair<string, double>> maxFlow;

    static int LINE_SIZE_;

public:
    void run();
    void load_data();
};


#endif //DOWNSTREAM_APP_H
