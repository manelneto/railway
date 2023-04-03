//
// Created by manue on 22/03/2023.
//

#ifndef RAILWAY_VERTEX_EDGE_H
#define RAILWAY_VERTEX_EDGE_H


#include <string>
#include <vector>

class Vertex;

/********************** Edge  ****************************/

class Edge {
public:
    enum Service {STANDARD, ALFA, OTHER};
    Edge(Vertex *orig, Vertex *dest, unsigned capacity, Service service);
    Vertex * getOrig() const;
    Vertex * getDest() const;
    unsigned getCapacity() const;
    Service getService() const;
    unsigned getCost() const;
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
    unsigned cost;
    unsigned flow = 0;
    bool selected = false;
    Edge * reverse = nullptr;
};

/************************* Vertex  **************************/

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

#endif //RAILWAY_VERTEX_EDGE_H
