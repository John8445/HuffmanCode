#include "GraphVertex.hpp"
#include <vector>

void GraphVertex::removeGraphEdge( std::string label1, std::string label2) {

    //iterate throught the vertexs edge vector till you find the desired edge and remove it

    for (size_t i = 0; i < adjacentVerteces.size(); i++) {
        if( /*(adjacentVerteces.at(i)->edgeWeight == edgeToRemoveWeight) && */
          ( (adjacentVerteces.at(i)->vertPointLeft->vertLabel == label1 && adjacentVerteces.at(i)->vertPointRight->vertLabel == label2)
            ||
            (adjacentVerteces.at(i)->vertPointLeft->vertLabel == label2 && adjacentVerteces.at(i)->vertPointRight->vertLabel == label1) ) )
        {
            adjacentVerteces.erase(adjacentVerteces.begin() + i);
        }

    }

}