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
    Edge(Vertex *orig, Vertex *dest, double w);
    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest;
    double weight;
    bool selected = false;
    Vertex *orig;
    Edge *reverse = nullptr;
    double flow;
};

#endif //RAILWAY_VERTEX_EDGE_H
