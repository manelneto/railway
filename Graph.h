//
// Created by manue on 22/03/2023.
//

#ifndef RAILWAY_GRAPH_H
#define RAILWAY_GRAPH_H

#include <list>
#include <queue>
#include "EdgeVertex.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id, const std::string &label);
    bool addEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service) const;
    bool addBidirectionalEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service) const;;
    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
    void edmondsKarp(int source, int target) const;
    void clear();
    unsigned getFlow(const int &id) const;
    unsigned maxFlow() const;
    unsigned maxFlow(std::list<std::pair<std::string, std::string>> &pairs) const;
    void addSuperSource(const int &id);
    void removeSuperSource() const;
    void removeEdge(const int &source, const int &target);
    void dijsktra(int source, int target) const;

private:
    std::vector<Vertex *> vertexSet;
    double **distMatrix = nullptr;
    int **pathMatrix = nullptr;
    int findVertexIdx(const int &id) const;
    static void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    bool findAugmentingPath(Vertex *s, Vertex *t) const;
    static unsigned findMinResidualAlongPath(Vertex *s, Vertex *t);
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, unsigned f);
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //RAILWAY_GRAPH_H
