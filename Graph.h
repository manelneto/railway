//
// Created by manue on 22/03/2023.
//

#ifndef RAILWAY_GRAPH_H
#define RAILWAY_GRAPH_H


#include "EdgeVertex.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &idStation) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */


    bool addVertex(const int &idStation);
    bool addEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service);
    bool addBidirectionalEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service);;
    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

    ;

private:
    std::vector<Vertex *> vertexSet;
    double ** distMatrix = nullptr;
    int **pathMatrix = nullptr;
    int findVertexIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


#endif //RAILWAY_GRAPH_H
