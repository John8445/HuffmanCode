#include "Graph.hpp"
#include <algorithm>


void Graph::addVertex(std::string label) {

    GraphVertex *tempVertex = new GraphVertex;
    tempVertex->vertLabel = label;

    vertexList.push_back(tempVertex);

}




void Graph::removeVertex(std::string label) {

    std::string firstVertexLabel = "";
    std::string secondVertexLabel = "";
    int indexOfVector = 0;
    //size_t endOfVertexList = vertexList.size();
    //size_t endOfVertexEdgeList = 0;

    //find the vertex to remove 
    for(size_t i = 0; i < vertexList.size(); i++) {

        if(vertexList.at(i)->vertLabel == label) {
            indexOfVector = i;
        }

    }

    //traverse every vertex vertexVector and remove the vector
    for(size_t i = 0; i < vertexList.size(); i++ ) {

        for(size_t j = 0; j < vertexList.at(i)->vertexVector.size(); j++) {
            if(vertexList.at(i)->vertexVector.at(j)->vertLabel == label) {
                vertexList.at(i)->vertexVector.erase(vertexList.at(i)->vertexVector.begin() + j);
            }
        }
    } 

    //go through all the edges in the vertex and remove them
    //( i < vertexList.at(indexOfVector)->adjacentVerteces.size(); i++)
    while( !(vertexList.at(indexOfVector)->adjacentVerteces.empty() ) )  {
        
        firstVertexLabel = vertexList.at(indexOfVector)->adjacentVerteces.at(0)->vertPointLeft->vertLabel;
        secondVertexLabel = vertexList.at(indexOfVector)->adjacentVerteces.at(0)->vertPointRight->vertLabel;

        //this function removes the edge from the edge list as well
        removeEdge(firstVertexLabel, secondVertexLabel);

    }

    //lastly delete the vertex which will delete all of its edges as well
    vertexList.erase(vertexList.begin() + indexOfVector);


}




void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {

    GraphEdge *tempEdge = new GraphEdge();

    tempEdge->edgeWeight = weight;

    int end = vertexList.size();
    int indexOfLabel1 = 0;
    int indexOfLabel2 = 0;

    for(int i = 0; i < end; i++) {

        if(vertexList.at(i)->vertLabel == label1 ) {
            //connect left pointer to first vertex
            tempEdge->vertPointLeft = vertexList.at(i);
            vertexList.at(i)->adjacentVerteces.push_back(tempEdge);
            indexOfLabel1 = i;
        }

        if(vertexList.at(i)->vertLabel == label2 ) { 
            //connect right pointer to second vertex
            tempEdge->vertPointRight = vertexList.at(i);                      
            vertexList.at(i)->adjacentVerteces.push_back(tempEdge);
            indexOfLabel2 = i;
        }

    }

    vertexList.at(indexOfLabel1)->vertexVector.push_back(vertexList.at(indexOfLabel2));
    vertexList.at(indexOfLabel2)->vertexVector.push_back(vertexList.at(indexOfLabel1));


    //add the edge to edgeVector
    edgeList.push_back(tempEdge);
    
}  




void Graph::removeEdge(std::string label1, std::string label2) {

    //first remove the vertexs from each vertexs vertexVector
    for(size_t i = 0; i < vertexList.size(); i++ ) {

            if(vertexList.at(i)->vertLabel == label1) {

                for(size_t j = 0; j < vertexList.at(i)->vertexVector.size(); j++)  {

                    if(label2 == vertexList.at(i)->vertexVector.at(j)->vertLabel) {

                        vertexList.at(i)->vertexVector.erase(vertexList.at(i)->vertexVector.begin() + j);

                    }
                }
            }

            if(vertexList.at(i)->vertLabel == label2) {

                for(size_t j = 0; j < vertexList.at(i)->vertexVector.size(); j++)  {

                    if(label1 == vertexList.at(i)->vertexVector.at(j)->vertLabel) {

                        vertexList.at(i)->vertexVector.erase(vertexList.at(i)->vertexVector.begin() + j);

                    }
                }
            }           
        
    } 


    for (size_t i = 0; i < vertexList.size(); i++) {

        if(vertexList.at(i)->vertLabel == label1) {
            vertexList.at(i)->removeGraphEdge( label1, label2);
        }

        if(vertexList.at(i)->vertLabel == label2) {
            vertexList.at(i)->removeGraphEdge( label1, label2);
        }
    }



    //find the edge in edge list and secure its weight and delete it from the edge vector
    for (size_t i = 0; i < edgeList.size(); i++) {

        if( (edgeList.at(i)->vertPointLeft->vertLabel == label1 && edgeList.at(i)->vertPointRight->vertLabel == label2) ||
            (edgeList.at(i)->vertPointLeft->vertLabel == label2 && edgeList.at(i)->vertPointRight->vertLabel == label1) )
            {
                edgeList.erase(edgeList.begin() + i);
            }

    }



}




unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {

    std::vector<GraphVertex> visitedVertexs;
    std::vector<GraphVertex> unvisitedVertexs;
    std::map<std::string, int> distance;
    std::map<std::string, std::string> previousVertex;
    int bigNumber = 1222333;

    //unsigned long distanceOfPath = 0;

    int edgeWeight = 0;

    int newDistance = 0;
    

    //load vector unvisited vertex and both maps with every vertex, map distance get a big number for distance
    for(size_t i = 0; i < vertexList.size(); i++) {
        GraphVertex tempVertex;
        tempVertex = *vertexList.at(i);
        unvisitedVertexs.push_back(tempVertex);
        distance.insert(std::pair<std::string, int>(vertexList.at(i)->vertLabel, bigNumber));
        previousVertex.insert(std::pair<std::string, std::string>(vertexList.at(i)->vertLabel, ""));
    }

    //set the distance for the start vertex to 0
    distance[startLabel] = 0;

    int index = 0;
    int possiblyShortest = 1222333;

    //start the while loop while unvisted vector is not empty
    while(!unvisitedVertexs.empty()) {

        possiblyShortest = 1222333;

        //we want to find the vertex with the smallest distance from the start vertex
        for(size_t i = 0; i < unvisitedVertexs.size(); i++) {

            if(possiblyShortest > distance[unvisitedVertexs.at(i).vertLabel] )  {
                possiblyShortest = distance[unvisitedVertexs.at(i).vertLabel];
                index = i;
            }

        }

        //look at unvisited adjacent vertices 
        for (size_t i = 0; i < unvisitedVertexs.at(index).vertexVector.size(); i++) {

            for ( size_t j = 0; j < unvisitedVertexs.size(); j++ ) {

                //if this adjacent vertex is unvisited 
                if(unvisitedVertexs.at(index).vertexVector.at(i)->vertLabel == unvisitedVertexs.at(j).vertLabel) {

                      //find the edge weight and its unvisited adjacent vertex
                    for(size_t x = 0; x < edgeList.size(); x++) {
                                                                            //this stores current vertex were looking at
                        if( ( (edgeList.at(x)->vertPointLeft->vertLabel == unvisitedVertexs.at(index).vertLabel && 
                            edgeList.at(x)->vertPointRight->vertLabel == unvisitedVertexs.at(index).vertexVector.at(i)->vertLabel) ) || (
                             edgeList.at(x)->vertPointRight->vertLabel == unvisitedVertexs.at(index).vertLabel && 
                            edgeList.at(x)->vertPointLeft->vertLabel == unvisitedVertexs.at(index).vertexVector.at(i)->vertLabel ) )
                        {
                            edgeWeight = edgeList.at(x)->edgeWeight;
                        }
                        
                    }

                    newDistance = edgeWeight + distance[unvisitedVertexs.at(index).vertLabel];

                    if(newDistance < distance[unvisitedVertexs.at(index).vertexVector.at(i)->vertLabel]) {
                        distance[unvisitedVertexs.at(index).vertexVector.at(i)->vertLabel] = newDistance;
                        previousVertex[unvisitedVertexs.at(index).vertexVector.at(i)->vertLabel] = unvisitedVertexs.at(index).vertLabel;

                    }

                }

            }

        }


        visitedVertexs.push_back(unvisitedVertexs.at(index));

        unvisitedVertexs.erase(unvisitedVertexs.begin() + index);



    }

    std::string temp = endLabel;
    path.push_back(temp);

    while(previousVertex[temp] != startLabel) {
        path.push_back(previousVertex[temp]);
        temp = previousVertex[temp];
    }

    path.push_back(startLabel);

    std::reverse(path.begin(), path.end());

    return distance[endLabel];


} 
    


void Graph::printGraph() {

    //int endOfVertexList = vertexList.size();
    //int endOfVertexEdgeList = 0;

    for (size_t i = 0; i < vertexList.size(); i++) {
        std::cout << "This is the vertex: " << vertexList.at(i)->vertLabel << std::endl;
        std::cout << "This is the edges associated with it: ";
        //endOfVertexEdgeList = vertexList.at(i)->adjacentVerteces.size();

        for(size_t x = 0; x < vertexList.at(i)->adjacentVerteces.size(); x++) {
            std::cout << vertexList.at(i)->adjacentVerteces.at(x)->edgeWeight << " ";
        }

        std::cout << std::endl << std::endl;
    }
}


void Graph::printAdjacencyList() {

    std::cout << std::endl;

    for (size_t i = 0; i < vertexList.size(); i++) {

        std::cout << "Vertex: " << vertexList.at(i)->vertLabel << " -- ";

        for(size_t j = 0; j < vertexList.at(i)->vertexVector.size(); j++) {

            std::cout << vertexList.at(i)->vertexVector.at(j)->vertLabel << "_";

        }


        std::cout << std::endl;
    }

    std::cout << std::endl;

}