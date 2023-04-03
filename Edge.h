//
// Created by manue on 03/04/2023.
//

#ifndef RAILWAY_EDGE_H
#define RAILWAY_EDGE_H


class Vertex;

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


#endif //RAILWAY_EDGE_H
