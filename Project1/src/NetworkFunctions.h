#ifndef PROJETO_NETWORKFUNCTIONS_H
#define PROJETO_NETWORKFUNCTIONS_H

#include "NetworkGraph.h"
#include <set>
#include <map>
#include <sstream>

bool findAugmentingPaths(NetworkGraph* g, Vertex* source, Vertex* sink);
void testAndVisit(queue<Vertex*> &q, Edge* e, Vertex* w, double residual);
double findMinResidualAlongPath(Vertex* source, Vertex* sink);
void augmentFlowAlongPath(Vertex* source, Vertex* sink, double flow);
void edmondsKarp(NetworkGraph* g, string source, string sink);
void megaEdmondsKarp(NetworkGraph *g, map<int, pair<string, double>> &maxFlow);
void allMaxFlow(map<int, pair<string,double>> &maxFlow);
void NameMaxFlow(map<int, pair<string, double>> &maxFlow, string cityName);
void CodeMaxFlow(map<int, pair<string,double>> &maxFlow, string cityCode);
void DeficitCalculator(NetworkGraph& g, map<int, pair<string, double>> &maxFlow);
void NetworkResiliency(NetworkGraph g, map<int, pair<string, double>> &maxFlow, string source);
void PipesResiliency(NetworkGraph g, map<int, pair<string, double>> &maxFlow, vector<pair<string, string>> pipes);
void pipesByCity(NetworkGraph g, map<int, pair<string, double>> &maxFlow, string code);
vector<pair<string, string>> pipeCollector();


#endif //PROJETO_NETWORKFUNCTIONS_H



