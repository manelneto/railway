//
// Created by manue on 22/03/2023.
//

#ifndef RAILWAY_GRAPH_H
#define RAILWAY_GRAPH_H


#include "EdgeVertex.h"

class Graph {
public:
    ~Graph();
    Vertex *findVertex(const int &id) const;
    bool addVertex(const int &id);
    bool addEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service);
    bool addBidirectionalEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service);
    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
private:
    std::vector<Vertex *> vertexSet;
    double ** distMatrix = nullptr;
    int **pathMatrix = nullptr;
    int findVertexIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


#endif //RAILWAY_GRAPH_H
