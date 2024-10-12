
#include "App.h"
using namespace std;

int App::LINE_SIZE_ = 119;

// sleep function

inline void my_sleep(int seconds) {
    #ifdef _WIN32
        Sleep(seconds * 1000); // Windows uses milliseconds
    #else
        sleep(seconds); // Unix-like systems use seconds
    #endif
}

// variables to help with menu switching

map<string, int> menus_map = {{"load_data", 0}, {"main", 1}};
stack<string> menus_stack;
bool over = false;
bool quit = false;

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that clears the stack.
 * @details Time Complexity: O(n).
 * */

void App::clearMenus() {
    while (!menus_stack.empty()) {
        menus_stack.pop();
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that calls a function depending on the user choice in the main menu.
 * @details Time Complexity: O(n).
 * */

void App::run() {
    clearMenus();
    menus_stack.emplace("load_data");
    while (true) {
        string next = menus_stack.top();
        switch (menus_map.at(next)) {
            case 0:
                //my_sleep(2);
                load_data();
                break;
            case 1:
                //my_sleep(2);
                mainMenu();
                break;
            default:
                quit = true;
        }
        if (over) {
            int op = 0;
            cout << endl;
            cout << string(LINE_SIZE_, '-') << endl;
            cout << "1 - Return to Load Menu" << endl;
            cout << "2 - Return to Main Menu" << endl;
            cout << "0 - Exit." << endl;
            cout << string(LINE_SIZE_, '-') << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> op) {
                    if (op == 0) {
                        quit = true;
                        break;
                    }
                    else if (op == 1) {
                        clearMenus();
                        menus_stack.emplace("load");
                        break;
                    }
                    else if (op == 2) {
                        clearMenus();
                        menus_stack.emplace("main");
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be between 0 and 2." << endl;
                    }
                }
                else {
                    cout << "Invalid input! Please enter a valid number." << endl;
                    cin.clear();          // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                }
            }
            over = false;
        }
        if (quit) break;
    }
    system("exit");
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that allows the user to load the data from the csv files.
 * @details Time Complexity: O(n).
 * */

void App::load_data() {
    graph = Graph();
    nodes.clear();

    vector<string> toy = {"shipping.csv", "stadiums.csv", "tourism.csv"};
    vector<string> fully_connected = {"edges_25.csv", "edges_50.csv", "edges_75.csv", "edges_100.csv", "edges_200.csv", "edges_300.csv", "edges_400.csv", "edges_500.csv", "edges_600.csv", "edges_700.csv", "edges_800.csv", "edges_900.csv"};
    vector<string> real = {"graph1", "graph2", "graph3"};


    cout << string(LINE_SIZE_, '-') << endl;
    cout << "Ocean Shipping & Urban Deliveries Management App." << endl;
    cout << string(LINE_SIZE_, '-') << endl;
    cout << "1 - Load a toy graph" << endl;
    cout << "2 - Load a fully connected graph" << endl;
    cout << "3 - Load a real world graph" << endl;
    cout << "4 - End." << endl;
    cout << string(LINE_SIZE_, '-') << endl;
    string file;
    int option;
    int size;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> size) {
            if (size == 1 || size == 2 || size == 3) {
                cout << endl;
                break;
            }
            else if (size == 4) {
                quit = true;
                return;
            }
            else {
                cout << "Invalid number! The number should be between 0 and 1." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
        }
    }


    switch (size) {
        case 1:
            cout << string(LINE_SIZE_, '-') << endl;
            cout << "1 - shipping" << endl;
            cout << "2 - stadiums" << endl;
            cout << "3 - tourism" << endl;
            cout << string(LINE_SIZE_, '-') << endl;
            cout << "Select the graph number (1 - 3): " << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> option) {
                    if (option > 0 && option < 4) {
                        file = toy[option - 1];
                        cout << endl;
                        read_from_toyGraph(&graph, &nodes, file);
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be between 1 and 3." << endl;
                    }
                }
                else {
                    cout << "Invalid input! Please enter a valid number." << endl;
                    cin.clear();          // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                }
            }
            break;
        case 2:
            cout << "Select the graph number (1 - 12): " << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> option) {
                    if (option > 0 && option < 13) {
                        file = fully_connected[option - 1];
                        cout << endl;
                        read_from_fullyConnectedGraph(&graph, &nodes, file);
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be between 1 and 12." << endl;
                    }
                }
                else {
                    cout << "Invalid input! Please enter a valid number." << endl;
                    cin.clear();          // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                }
            }
            break;
        case 3:
            cout << "Select the graph number (1 - 3): " << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> option) {
                    if (option > 0 && option < 4) {
                        file = real[option - 1];
                        cout << endl;
                        read_from_realGraph(&graph, &nodes, file);
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be between 1 and 3." << endl;
                    }
                }
                else {
                    cout << "Invalid input! Please enter a valid number." << endl;
                    cin.clear();          // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                }
            }
            break;
        case 4:
            quit = true;
            return;
        default:
            break;
    }

    menus_stack.emplace("main");
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that runs the main menu of the app.
 * @details Time Complexity: O(n).
 * */

void App::mainMenu() {
    int op;

    cout << string(LINE_SIZE_, '-') << endl;
    cout << "1 - Backtracking." << endl;
    cout << "2 - Triangular approximation." << endl;
    cout << "3 - Cheapest Insertion Algorithm." << endl;
    cout << "4 - TSP in the Real World." << endl;
    cout << "5 - Return to load menu." << endl;
    cout << "0 - End." << endl;
    cout << string(LINE_SIZE_, '-') << endl;

    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            cout << endl;
            vector<Vertex*> bestPath;
            switch (op) {
                case 1 :{
                    auto start = chrono::high_resolution_clock::now();
                    TourResult backtracking = findTSP(&graph);
                    // Function whose execution time you want to measure
                    cout << "The distance of the path is: " << backtracking.totalDistance << "." << endl;
                    cout << backtracking.tour.at(0)->getInfo();
                    for (auto v : backtracking.tour) {
                        if (v != backtracking.tour.at(0)) cout << " -> " << v->getInfo();
                    }
                    cout << " -> " << backtracking.tour.at(backtracking.tour.size() - 1)->getInfo();
                    cout << endl;

                    // Get the end time
                    auto end = chrono::high_resolution_clock::now();

                    // Calculate and print the duration
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    cout << endl << "Execution time: " << duration.count() << " milliseconds." << endl;

                    return;
                }
                case 2 : {
                    auto start = chrono::high_resolution_clock::now();
                    TourResult triangular = triangularApproximation(&graph);

                    if (triangular.tour.empty()) {
                        cout << "This algorithm is incompatible with the provided graph." << endl;
                        return;
                    }
                    // Function whose execution time you want to measure
                    cout << "The distance of the path is: " << triangular.totalDistance << "." << endl;
                    cout << triangular.tour.at(0)->getInfo();
                    for (auto v : triangular.tour) {
                        if (v != triangular.tour.at(0)) cout << " -> " << v->getInfo();
                    }
                    cout << " -> " << triangular.tour.at(triangular.tour.size() - 1)->getInfo();
                    cout << endl;

                    // Get the end time
                    auto end = chrono::high_resolution_clock::now();

                    // Calculate and print the duration
                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    cout << "Execution time: " << duration.count() << " milliseconds." << endl;

                    return;
                }
                case 3 : {
                    auto start = chrono::high_resolution_clock::now();
                    TourResult ci = cheapestInsertion(&graph);
                    cout << "The total distance is " << ci.totalDistance << endl;
                    cout << ci.tour.at(0)->getInfo();
                    for (int i = 1; i < ci.tour.size(); i++) {
                        cout << " -> " << ci.tour[i]->getInfo();
                    }
                    cout << endl;
                    auto end = chrono::high_resolution_clock::now();

                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    cout << "Execution time: " << duration.count() << " milliseconds." << endl;
                    return;
                }
                case 4: {
                    auto start = chrono::high_resolution_clock::now();

                    int n = 0;
                    while (true) {
                        cout << "Write the number of node: ";
                        if (cin >> n) {
                            if (n < graph.getVertexSet().size()) {
                                break;
                            }
                            else {
                                cout << "Invalid number! The number should be lower than " << graph.getVertexSet().size() << "." << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                        }
                    }

                    realWorld(graph, n);

                    auto end = chrono::high_resolution_clock::now();

                    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                    cout << "Execution time: " << duration.count() << " milliseconds." << endl;
                    return;
                }
                case 5:
                    clearMenus();
                    menus_stack.emplace("load_data");
                    return;
                case 0:
                    quit = true;
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 4." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}