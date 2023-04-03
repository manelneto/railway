//
// Created by manue on 03/04/2023.
//

#ifndef RAILWAY_VERTEX_H
#define RAILWAY_VERTEX_H


#include <string>
#include <vector>
#include "Edge.h"

class Vertex {
public:
    Vertex(int id, const std::string &label);
    int getId() const;
    const std::string &getLabel() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned getIndegree() const;
    unsigned getCost() const;
    Edge * getPath() const;
    std::vector<Edge *> getIncoming() const;
    void setId(int id);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned indegree);
    void setCost(unsigned cost);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, unsigned capacity, Edge::Service service);
    bool removeEdge(int destID);
    void removeOutgoingEdges();
    bool operator<(Vertex &v1) const;
    int queueIndex;
private:
    int id;
    std::string label;
    std::vector<Edge *> adj;
    bool visited = false;
    bool processing = false;
    unsigned indegree = 0;
    unsigned cost = 0;
    Edge * path = nullptr;
    std::vector<Edge *> incoming;
    void deleteEdge(Edge *edge) const;
};


#endif //RAILWAY_VERTEX_H
