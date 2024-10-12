//
// Created by franciscoafonso on 23-04-2024.
//

#ifndef TSP_PARSINGFUNCTIONS_H
#define TSP_PARSINGFUNCTIONS_H


#include "Graph.h"
using namespace std;

int check_vertices(string path);
void read_from_toyGraph(Graph* graph, set<Vertex*>* nodes, string file);
void read_from_fullyConnectedGraph(Graph* graph, set<Vertex*>* nodes, string file);
void read_from_realGraph(Graph* graph, set<Vertex*>* nodes, string folder);
void read_from_nodes_fully_connected(Graph* graph, set<Vertex*>* nodes, string path, int n);
void read_from_nodes_real(Graph* graph, set<Vertex*>* nodes, string path);
void read_from_edges(Graph* graph, string path);



#endif //TSP_PARSINGFUNCTIONS_H
