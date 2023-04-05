//
// Created by manue on 03/04/2023.
//

#include "Vertex.h"

using namespace std;

Vertex::Vertex(int id, const string &label): id(id), label(label) {}

bool Vertex::operator<(Vertex & vertex) const {
    return this->cost < vertex.cost;
}

int Vertex::getId() const {
    return this->id;
}

const string &Vertex::getLabel() const {
    return this->label;
}

vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

unsigned Vertex::getCost() const {
    return this->cost;
}

Edge * Vertex::getPath() const {
    return this->path;
}

vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setCost(unsigned cost) {
    this->cost = cost;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

Edge * Vertex::addEdge(Vertex *d, unsigned capacity, Edge::Service service) {
    auto newEdge = new Edge(this, d, capacity, service);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true;
        }
        else
            it++;
    }
    return removedEdge;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

void Vertex::deleteEdge(Edge *edge) const {
    Vertex *dest = edge->getDest();
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end())
        if ((*it)->getOrig()->getId() == id)
            it = dest->incoming.erase(it);
        else
            it++;
    delete edge;
}
