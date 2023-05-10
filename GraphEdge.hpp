#ifndef GRAPH_EDGE
#define GRAPH_EDGE

#include "GraphVertex.hpp"
#include "Graph.hpp"

class GraphVertex;

class GraphEdge {
    public:
        GraphEdge() {
            vertPointLeft = nullptr;
            vertPointRight = nullptr;
            edgeWeight = 0;
        }

    private: 
        GraphVertex *vertPointRight;
        GraphVertex *vertPointLeft;
        unsigned long edgeWeight;

        friend class Graph;
        friend class GraphVertex;

};



#endif