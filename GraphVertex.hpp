#ifndef GRAPH_VERTEX
#define GRAPH_VERTEX

#include <vector>
#include <map>
#include <string>
#include "GraphEdge.hpp"

class GraphEdge;

class GraphVertex {

    public:
        GraphVertex() { 
            isVisted = false;
            vertLabel = ""; 
        }
        void removeGraphEdge( std::string label1, std::string label2);


    private: 
        std::vector<GraphEdge*> adjacentVerteces;
        std::vector<GraphVertex*> vertexVector;
        std::string vertLabel;
        bool isVisted;
        
        friend class Graph;
        friend class GraphEdge;


};



#endif



