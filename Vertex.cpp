//
// Created by manue on 03/04/2023.
//

#include "Vertex.h"

using namespace std;

Vertex::Vertex(int id, const string &label): id(id), label(label) {}

int Vertex::getId() const {
    return this->id;
}

const std::string &Vertex::getLabel() const {
    return this->label;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

unsigned Vertex::getCost() const {
    return this->cost;
}

Edge * Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned indegree) {
    this->indegree = indegree;
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
    d->setIndegree(d->getIndegree() + 1);
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
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
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
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id)
            it = dest->incoming.erase(it);
        else
            it++;
    }
    delete edge;
}
bool Vertex::operator<(Vertex &v1) const{
    return this->getCost() < v1.getCost();
}
