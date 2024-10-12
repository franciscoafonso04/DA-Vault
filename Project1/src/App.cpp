#include "App.h"


int App::LINE_SIZE_ = 119;

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that runs the main menu of the app.
 * @details Time Complexity: O(1).
 * */

void App::run() {
    load_data();
    megaEdmondsKarp(&network, maxFlow);
    write_max_flow(&network, maxFlow);



    cout << string(LINE_SIZE_, '-') << endl;
    cout << "Welcome to the DownstreAm Water Supply Management App." << endl;
    start:
    cout << string(LINE_SIZE_, '-') << endl;
    cout << "1 - Consult maximum amount of water that can reach each city." << endl;
    cout << "2 - Consult maximum amount of water that can reach a specific city by name." << endl;
    cout << "3 - Consult maximum amount of water that can reach a specific city by code." << endl;
    cout << "4 - Consult the deficit between the city's demand and the actual flow." << endl;
    cout << "5 - Consult the affected cities by an out of commission reservoir." << endl;
    cout << "6 - Consult the affected cities by an out of service pumping station." << endl;
    cout << "7 - Consult the affected cities by ruptured pipes." << endl;
    cout << "8 - Consult the essential pipes for a city's water supply." << endl;
    cout << "9 - End." << endl;
    cout << string(LINE_SIZE_, '-') << endl;

    string decision,city, reservoir, pumping;
    vector<pair<string, string>> pipes;
    int valid = 0;
    getline(cin, decision);

    switch (decision[0]) {
        case '1':
            allMaxFlow(maxFlow);
            sleep(4);
            cout << endl;
            goto start;
        case '2':
            cout << "Input the desired city's name: ";
            getline(cin, city);
            NameMaxFlow(maxFlow, city);
            sleep(4);
            cout << endl;
            goto start;
        case '3':
            cout << "Input the desired city's code: ";
            getline(cin, city);
            CodeMaxFlow(maxFlow, city);
            sleep(4);
            cout << endl;
            goto start;
        case '4':
            DeficitCalculator(network, maxFlow);
            sleep(4);
            cout << endl;
            goto start;
        case '5':
            cout << "Input the desired reservoir's code: ";
            getline(cin, reservoir);
            for (auto v : reservoirs)
                if (v->getCode() == reservoir) {
                    valid++;
                    continue;
                }
            if (valid) NetworkResiliency(network, maxFlow, reservoir);
            else cout << "Invalid Reservoir." << endl;
            sleep(4);
            cout << endl;
            goto start;
        case '6':
            cout << "Input the desired pumping station's code: ";
            getline(cin, pumping);
            for (auto v : stations)  {
                if (v->getCode() == pumping) {
                    valid++;
                    continue;
                }
            }
            if (valid) NetworkResiliency(network, maxFlow, pumping);
            else cout << "Invalid Pumping Station." << endl;
            sleep(4);
            cout << endl;
            goto start;
        case '7':
            cout << "Input the source and destination codes separated by a ',', separate each pipe by a ';': ";
            pipes = pipeCollector();
            PipesResiliency(network, maxFlow, pipes);
            sleep(4);
            goto start;
        case '8':
            cout << "Input the desired city's code or name: ";
            getline(cin, city);
            pipesByCity(network, maxFlow, city);
            sleep(4);
            cout << endl;
            goto start;
        default:
            return;
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that allows the user to load the data from the csv files.
 * @details Time Complexity: O(1).
 * */

void App::load_data() {
    auto start = chrono::high_resolution_clock::now();

    read_from_cities(cities, network);
    read_from_reservoirs(reservoirs, network);
    read_from_stations(stations, network);
    read_from_pipes(network);

    auto megaSource = new Vertex("megaSource", 'M', "", 1, "M_1", INF);
    auto megaSink = new Vertex("megaSink", 2, 'M', "M_2", INF, 0.0);
    network.addVertex(megaSource);
    network.addVertex(megaSink);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end-start;
    double duration_sec = duration.count();
    cout << "Loaded " << reservoirs.size() << " Reservoirs (sources) " << stations.size() << " Pumping Stations and " << cities.size() << " cities (sinks)"
    << " in " << duration_sec << " seconds." << endl;
}

