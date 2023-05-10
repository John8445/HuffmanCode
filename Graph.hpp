#ifndef GRAPH
#define GRAPH

#include "GraphBase.hpp"
#include "GraphVertex.hpp"
#include "GraphEdge.hpp"
#include <vector>
#include <list>
#include <iostream>
#include <map>

class GraphVertex;
class GraphEdge;

class Graph : public GraphBase {

    public:
        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
        void printGraph();
        void printAdjacencyList();
    
    private:
        std::vector<GraphVertex*> vertexList;
        std::vector<GraphEdge*> edgeList;


};


#endif