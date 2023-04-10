//
// Created by manue on 03/04/2023.
//

#include "Edge.h"

Edge::Edge(Vertex *orig, Vertex *dest, unsigned capacity, Service service) : orig(orig), dest(dest), capacity(capacity),
                                                                             service(service) {
    if (service == STANDARD)
        cost = 2;
    else if (service == ALFA)
        cost = 4;
    else
        cost = -1;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

unsigned Edge::getCapacity() const {
    return this->capacity;
}

Edge::Service Edge::getService() const {
    return this->service;
}

unsigned int Edge::getCost() const {
    return this->cost;
}

unsigned Edge::getFlow() const {
    return flow;
}

void Edge::setFlow(unsigned flow) {
    this->flow = flow;
}
