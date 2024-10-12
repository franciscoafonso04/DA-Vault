#ifndef PROJETO_READFUNCTIONS_H
#define PROJETO_READFUNCTIONS_H

#include <string>
#include <fstream>
#include "NetworkFunctions.h"

void read_from_cities(set<Vertex*>& cities, NetworkGraph& network);

void read_from_reservoirs(set<Vertex*>& reservoirs, NetworkGraph& network);

void read_from_stations(set<Vertex*>& stations, NetworkGraph& network);

void read_from_pipes(NetworkGraph& network);

void write_max_flow(NetworkGraph *g, map<int, pair<string, double>> maxFlow);

#endif //PROJETO_READFUNCTIONS_H
