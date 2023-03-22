//
// Created by manue on 22/03/2023.
//

#ifndef RAILWAY_VERTEX_EDGE_H
#define RAILWAY_VERTEX_EDGE_H


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

class Edge;

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int id);
    bool operator<(Vertex & vertex) const;
    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;
    void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int destID);
    void removeOutgoingEdges();

private:
    int id;
    std::vector<Edge *> adj;
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    Edge *path = nullptr;
    std::vector<Edge *> incoming;
    int queueIndex = 0;
    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge {
public:
    enum Service {STANDARD, ALFA};
    Edge(Vertex *orig, Vertex *dest, unsigned capacity, Service service);
    Vertex * getOrig() const;
    Vertex * getDest() const;
    unsigned getCapacity() const;
    Service getService() const;
    unsigned getFlow() const;
    bool isSelected() const;
    Edge * getReverse() const;
    void setFlow(unsigned flow);
    void setSelected(bool selected);
    void setReverse(Edge * reverse);

private:
    Vertex * orig;
    Vertex * dest;
    unsigned capacity;
    Service service;

    unsigned flow;
    bool selected = false;
    Edge * reverse = nullptr;
};

#endif //RAILWAY_VERTEX_EDGE_H
