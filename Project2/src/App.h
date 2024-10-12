#ifndef TSP_APP_H
#define TSP_APP_H

#include "ParsingFunctions.h"
#include "BackTracking.h"
#include "TriangularApproximation.h"
#include "OtherHeuristics.h"
#include "RealWorld.h"
#include <stack>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/**
 * @brief Class that represents the main program interface and all of its stored data.
 */

class App {

    /** @brief set of vertices that stores all nodes. */
    set<Vertex*> nodes;

    /** @brief App's graph. */
    Graph graph;

    static int LINE_SIZE_;

public:
    void clearMenus();
    void run();
    void load_data();
    void mainMenu();
};


#endif //TSP_APP_H
