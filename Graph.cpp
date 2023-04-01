//
// Created by manue on 22/03/2023.
//

#include "Graph.h"

int Graph::getNumVertex() const {
    return (int) vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}

bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}

bool Graph::addEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, capacity, service);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, unsigned capacity, Edge::Service service) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, capacity, service);
    auto e2 = v2->addEdge(v1, capacity, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, (int) vertexSet.size());
    deleteMatrix(pathMatrix, (int) vertexSet.size());
}

void Graph::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for (auto v : vertexSet)
        v->setVisited(false);
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj())
            testAndVisit(q, e, e->getDest(), e->getCapacity() - e->getFlow());
        for (auto e: v->getIncoming())
            testAndVisit(q, e, e->getOrig(), e->getFlow());
    }
    return t->isVisited();
}

unsigned Graph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    unsigned f = UINT_MAX;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *s, Vertex *t, unsigned f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        unsigned flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

void Graph::edmondsKarp(int source, int target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    // Reset the flows
    for (auto v : vertexSet)
        for (auto e: v->getAdj())
            e->setFlow(0);

    // Loop to find augmentation paths
    while (findAugmentingPath(s, t)) {
        unsigned f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

void Graph::clear() {
    for (auto v : vertexSet)
        v->removeOutgoingEdges();
    vertexSet.clear();
}

unsigned Graph::getFlow(const int &id) const {
    unsigned flow = 0;
    const auto u = findVertex(id);
    for (const auto e : u->getIncoming())
        flow += e->getFlow();
    return flow;
}
