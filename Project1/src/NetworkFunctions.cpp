#include "NetworkFunctions.h"

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds all augmenting paths from vertex/location source to vertex/location sink of graph/network g.
 * @details Time Complexity: O(V + E).
 * @param source Pointer of source vertex/location.
 * @param sink Pointer of destination vertex/location.
 * @param g Graph/network.
 * @return true if it finds augmenting path.
 * */

bool findAugmentingPaths(NetworkGraph *g, Vertex* source, Vertex* sink) {
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    source->setVisited(true);
    queue<Vertex*> q;
    q.push(source);
    while (!q.empty() && !sink->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight()-e->getFlow());
        }
        for (auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return sink->isVisited();
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that test and visits vertex/location w.
 * @details Time Complexity: O(1).
 * @param q Queue of vertices/locations.
 * @param e Edge/Pipe to set as path of the vertex/location w.
 * @param w Vertex/location to be tested/visited.
 * @param residual capacity of path.
 * */

void testAndVisit(queue<Vertex*> &q, Edge* e, Vertex* w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that finds the residual capacities along path.
 * @details Time Complexity: O(V).
 * @param source Reservoir.
 * @param sink City.
 * @return residual capacity of the path.
 * */

double findMinResidualAlongPath(Vertex* source, Vertex* sink) {
    double f = INF;
    auto v = sink;
    while ( v != source) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that reduces flow value and increases the reverse flow value.
 * @details Time Complexity: O(V).
 * @param source Reservoir.
 * @param sink City.
 * @param f residual capacity of the path.
 * */

void augmentFlowAlongPath(Vertex* source, Vertex* sink, double f) {
    auto v = sink;
    while (v != source) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }

}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that represents the Edmonds Karp's Algorithm.
 * @details Time Complexity: O(V*E^2).
 * @param g Graph/Network.
 * @param source Reservoir.
 * @param sink City.
 * */

void edmondsKarp(NetworkGraph *g, string source, string sink) {
    auto s = g->findVertex(source);
    auto t = g->findVertex(sink);

    if (s == nullptr || t == nullptr || s==t ) {
        throw std::logic_error("Err0r");
    }
    for (auto v : g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    while (findAugmentingPaths(g, s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that creates a megaSource and a megaSink to calculate the maximum amount of water that reaches each city.
 * @details Time Complexity: O(V*E^2).
 * @param g Graph/Network.
 * @param maxFlow Map that will store the maximum amount of water that reach each city.
 * @param id auxliary int for the new vertices created along the function.
 * */

void megaEdmondsKarp(NetworkGraph* g, map<int, pair<string, double>> &maxFlow) {
    auto megaSource = g->findVertex("M_1");
    auto megaSink = g->findVertex("M_2");

    for(auto v: g->getVertexSet()) {
        if(v->getType() == 'R')
            g->addEdge(megaSource->getCode(), v->getCode(), v->getMaxDel());
        if(v->getType() == 'C')
            g->addEdge(v->getCode(), megaSink->getCode(), v->getDemand());
    }

    edmondsKarp(g, megaSource->getCode(), megaSink->getCode());

    for (auto e : megaSink->getIncoming()) {
        maxFlow[e->getOrig()->getId()] = make_pair(e->getOrig()->getName(), e->getFlow());
    }

    for(auto v: g->getVertexSet()) {
        if(v->getType() == 'R')
            g->removeEdge(megaSource->getCode(), v->getCode());
        if(v->getType() == 'C')
            g->removeEdge(v->getCode(), megaSink->getCode());
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that prints the maximum amount of water that reaches each city.
 * @details Time Complexity: O(V).
 * @param maxFlow Map that stores the maximum amount of water that reach each city.
 * */

void allMaxFlow(map<int, pair<string, double>> &maxFlow) {
    double sum = 0;
    for (auto v : maxFlow) {
        cout << "C_" << v.first << " | " << v.second.first << " | " << v.second.second << endl;
        sum+=v.second.second;
    }
    cout << "Sum: " << sum << endl;
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that prints the maximum amount of water that reaches a city with a given name.
 * @details Time Complexity: O(V).
 * @param maxFlow Map that stores the maximum amount of water that reach each city.
 * @param cityName in string format.
 * */

void NameMaxFlow(map<int, pair<string, double>> &maxFlow, string cityName) {
    for (auto v : maxFlow) {
        if (v.second.first == cityName) {
            cout << "C_" << v.first << " | " << v.second.first << " | " << v.second.second << endl;
            return;
        }
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that prints the maximum amount of water that reaches a city with a given code.
 * @details Time Complexity: O(V).
 * @param maxFlow Map that stores the maximum amount of water that reach each city.
 * @param cityCode in string format.
 * */

void CodeMaxFlow(map<int, pair<string,double>> &maxFlow, string cityCode) {
    string code;
    for (auto v : maxFlow) {
        code = "C_" + to_string(v.first);
        if (code == cityCode) {
            cout << code << " | " << v.second.first << " | " << v.second.second << endl;
            return;
        }
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that calculates and prints the deficit of water flow of each city.
 * @details Time Complexity: O(V).
 * @param maxFlow Map that stores the maximum amount of water that reach each city.
 * @param g Graph/Network.
 * */

void DeficitCalculator(NetworkGraph& g, map<int, pair<string, double>> &maxFlow){
    for(auto city: maxFlow){
        string code = "C_" + to_string(city.first);
        auto v = g.findVertex(code);
        double deficit = v->getDemand() - city.second.second;
        if(deficit > 0) cout << code << " | " << v->getName() << " | Demand: " << v->getDemand() << " | Actual Flow: " << city.second.second << " | Deficit: " << deficit << endl;
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that evaluates the network resiliency when removing a location from the graph.
 * @details Time Complexity: O(V).
 * @param g Graph/Network.
 * @param maxFlow Map that stores the maximum amount of water that reach each city.
 * @param source reservoir's code in string format.
 * */

void NetworkResiliency(NetworkGraph g, map<int, pair<string, double>> &maxFlow, string source) {
    auto v_source = g.findVertex(source);
    for(auto e: v_source->getAdj())
        e->setWeight(0);

    map<int, pair<string, double>> newMaxFlow;

    megaEdmondsKarp(&g, newMaxFlow);

    auto oldCity = maxFlow.begin();
    auto newCity = newMaxFlow.begin();

    bool dif = false;
    while(oldCity != maxFlow.end()){
        string code = "C_" + to_string(oldCity->first);

        auto oldV = g.findVertex(code);
        auto newV = g.findVertex(code);

        double oldDeficit = oldV->getDemand() - oldCity->second.second;
        double newDeficit = newV->getDemand() - newCity->second.second;

        double deficit = oldCity->second.second - newCity->second.second;

        if(newDeficit != oldDeficit and newDeficit != 0 and deficit > 0) {
            cout << code << " | " << oldV->getName() << " | Old Flow: " << oldCity->second.second << " | New Flow: " << newCity->second.second <<" | Deficit: " << deficit << endl;
            dif = true;
        }

        ++oldCity;
        ++newCity;
    }

    for(auto e: v_source->getAdj())
        e->setWeight(e->getWeightAux());

    if(!dif){
        if(source[0] == 'R')
            cout << "The out of commission reservoir had no effect on the network." << endl;
        else if(source[0] == 'P')
            cout << "The out of service pumping station had no effect on the network." << endl;
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that evaluates the network resiliency when removing one or various pipes from the graph.
 * @details Time Complexity: O(V).
 * @param g Graph/Network.
 * @param maxFlow Map that stores the maximum amount of water that reach each city.
 * @param pipes Vector that stores the pipes to be removed.
 * */

void PipesResiliency(NetworkGraph g, map<int, pair<string, double>> &maxFlow, vector<pair<string, string>> pipes) {

    for(auto p: pipes) {
        auto e = g.findEdge(p.first, p.second);
        e->setWeight(0);
        if(e->getReverse() != nullptr)
            e->getReverse()->setWeight(0);
    }

    map<int, pair<string, double>> newMaxFlow;

    megaEdmondsKarp(&g, newMaxFlow);

    auto oldCity = maxFlow.begin();
    auto newCity = newMaxFlow.begin();

    bool dif = false;
    while(oldCity != maxFlow.end()){
        string code = "C_" + to_string(oldCity->first);

        auto oldV = g.findVertex(code);
        auto newV = g.findVertex(code);

        double oldDeficit = oldV->getDemand() - oldCity->second.second;
        double newDeficit = newV->getDemand() - newCity->second.second;

        double deficit = oldCity->second.second - newCity->second.second;

        if(newDeficit != oldDeficit and newDeficit != 0 and deficit > 0) {
            cout << code << " | " << oldV->getName() << " | Old Flow: " << oldCity->second.second << " | New Flow: " << newCity->second.second <<" | Deficit: " << deficit << endl;
            dif = true;
        }

        ++oldCity;
        ++newCity;
    }

    for(auto p: pipes) {
        auto e = g.findEdge(p.first, p.second);
        e->setWeight(e->getWeightAux());
        if(e->getReverse() != nullptr)
            e->getReverse()->setWeight(e->getWeightAux());
    }

    if(!dif){
        if(pipes.size() == 1)
            cout << "The ruptured pipe had no effect on the network." << endl;
        else
            cout << "The ruptured pipes had no effect on the network." << endl;
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that prints the pipes that affect a certain city's flow.
 * @details Time Complexity: O(V*E).
 * @param g Graph/Network.
 * @param maxFlow Map that stores the maximum amount of water that reach each city.
 * @param code or name of city in string format.
 * */

void pipesByCity(NetworkGraph g, map<int, pair<string, double>> &maxFlow, string code) {

    if(code[1] != '_')
        for(auto v: g.getVertexSet()) if(v->getName() == code) code = v->getCode();

    for (auto v: g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            double weight = e->getWeight();
            e->setWeight(0);

            map<int, pair<string, double>> newMaxFlow;
            megaEdmondsKarp(&g, newMaxFlow);

            string sId;
            if (code.length() == 4) sId = code.substr(2, 2);
            else if (code.length() == 5) sId = code.substr(2, 3);
            else sId = code.substr(2, 1);

            int id = stoi(sId);

            auto city = g.findVertex(code);
            double oldDeficit = city->getDemand() - maxFlow[id].second;
            double newDeficit = city->getDemand() - newMaxFlow[id].second;
            double difference = maxFlow[id].second - newMaxFlow[id].second;

            if (difference > 0) {
                cout << "The pipe from " << e->getOrig()->getCode() << " to " << e->getDest()->getCode()
                     << " is essential to the city." << endl;
                cout << "Old Deficit: " << oldDeficit << " | New Deficit: " << newDeficit << " | Difference: "
                     << difference << endl << endl;
            }

            e->setWeight(weight);
        }
    }
}

/** -------------------------------------------------------------------------------------------------------------------------
 * @brief Function that receives the list pipes inputted by the user.
 * @details Time Complexity: O(n).
 * @return the choice of the user in the format of a vector of pairs of strings.
 * */

vector<pair<string, string>> pipeCollector(){
    vector<pair<string, string>> pipes;
    vector<string> pipes_raw;
    string code_vec, code;

    getline(cin, code_vec);
    istringstream iss(code_vec);
    while (!iss.eof()) {
        getline(iss,code,';');
        pipes_raw.push_back(code);
    }

    for(auto s: pipes_raw){
        istringstream iss2(s);
        string source, dest;
        pair<string, string> pipe;
        getline(iss2, source, ',');
        getline(iss2, dest, ',');
        pipe.first = source;
        pipe.second = dest;
        pipes.push_back(pipe);
    }

    return pipes;
}































/*
/*void MeanVariance(NetworkGraph g, double& mean, double& variance){
    double n = 0;

    for(auto v: g.getVertexSet())
        for(auto e: v->getAdj()) {
            mean += e->getFlow();
            n++;
        }
    mean /= n;

    for(auto v: g.getVertexSet())
        for(auto e: v->getAdj())
            variance += (e->getFlow() - mean) * (e->getFlow() - mean);
    variance /= n;
}*/

/*
void BalancingMission(NetworkGraph g){
    double mean = 0, variance = 0;
    MeanVariance(g, mean, variance);
    cout << "initial mean: " << mean << endl;
    cout << "initial variance: " << variance << endl;

    map<int, pair<string, double>> oldMaxFlow;
    megaEdmondsKarp(&g, oldMaxFlow, 17);

    for(auto v: g.getVertexSet()){
        if(v->getType() == 'C'){
            int sum = 0;
            for(auto e: v->getIncoming()){
                sum += e->getFlow();
            }
        }
    }

}
 */





























