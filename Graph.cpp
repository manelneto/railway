//
// Created by manue on 22/03/2023.
//

#include "Graph.h"
#include "MutablePriorityQueue.h"
#include <stdexcept>
#include <climits>

using namespace std;

Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

bool Graph::addVertex(const int &id, const string &label) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, label));
    return true;
}

bool Graph::addEdge(const int &source, const int &dest, unsigned capacity, Edge::Service service) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, capacity, service);
    return true;
}

bool Graph::addBidirectionalEdge(const int &source, const int &dest, unsigned capacity, Edge::Service service) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    for (const auto edge : v1->getAdj())
        if (edge->getDest()->getId() == dest && edge->getCapacity() == capacity && edge->getService() == service)
            return false;
    v1->addEdge(v2, capacity, service);
    v2->addEdge(v1, capacity, service);
    return true;
}

unsigned Graph::getNumVertex() const {
    return vertexSet.size();
}

void Graph::edmondsKarp(int source, int target) const {
    Vertex *s = findVertex(source);
    Vertex *t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw logic_error("Invalid source and/or target vertex");

    for (auto v : vertexSet)
        for (auto e: v->getAdj())
            e->setFlow(0);

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

unsigned Graph::sumFlow() const {
    unsigned sum = 0;
    for (const auto &u : vertexSet)
        for (const auto &v : vertexSet) {
            if (v->getId() <= u->getId())
                continue;
            edmondsKarp(u->getId(), v->getId());
            unsigned flow = getFlow(v->getId());
            sum += flow;
        }
    return sum;
}

unsigned Graph::maxFlow(list<pair<string, string>> &pairs) const {
    unsigned max = 0;
    for (const auto &u : vertexSet)
        for (const auto &v : vertexSet) {
            if (v->getId() <= u->getId())
                continue;
            edmondsKarp(u->getId(), v->getId());
            unsigned flow = getFlow(v->getId());
            if (flow > max) {
                max = flow;
                pairs.clear();
                pairs.emplace_back(u->getLabel(), v->getLabel());
            } else if (flow == max)
                pairs.emplace_back(u->getLabel(), v->getLabel());
        }
    return max;
}

void Graph::addSuperSource(const int &id) {
    addVertex(0, "Super Source");
    for (const auto &v : vertexSet)
        if (v->getIndegree() <= 1 && v->getId() != id)
            addEdge(0, v->getId(), UINT_MAX, Edge::OTHER);
}

void Graph::removeSuperSource() const {
    Vertex *superSource = findVertex(0);
    for (const auto it : superSource->getAdj())
        it->getDest()->setIndegree(it->getDest()->getIndegree() - 1);
    superSource->removeOutgoingEdges();
}

bool Graph::removeEdge(const int &source, const int &target) const {
    Vertex *s = findVertex(source);
    Vertex *t = findVertex(target);
    return (s->removeEdge(target) && t->removeEdge(source));
}

void Graph::dijkstra(int source) const {
    MutablePriorityQueue<Vertex> queue;
    for (const auto vertex : vertexSet) {
        vertex->setCost(INT_MAX);
        vertex->setPath(nullptr);
        queue.insert(vertex);
    }
    Vertex *s = findVertex(source);
    s->setCost(0);
    s->setPath(nullptr);
    queue.decreaseKey(s);
    while (!queue.empty()) {
        Vertex *u = queue.extractMin();
        for (Edge *e: u->getAdj()) {
            Vertex *v = e->getDest();
            if (relax(u, v, e))
                queue.decreaseKey(v);
        }
    }
}

unsigned Graph::getPathFlow(int target) const {
    Vertex *t = findVertex(target);
    unsigned minCut = UINT_MAX;
    for (Edge *e = t->getPath(); e != nullptr; e = e->getOrig()->getPath())
        if (e->getCapacity() < minCut)
            minCut = e->getCapacity();
    if (minCut == UINT_MAX)
        minCut = 0;
    return minCut;
}

unsigned Graph::getPathCost(int target, unsigned flow) const {
    Vertex *t = findVertex(target);
    unsigned cost = 0;
    for (Edge *e = t->getPath(); e != nullptr; e = e->getOrig()->getPath())
        cost += flow * e->getCost();
    return cost;
}

void Graph::testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, unsigned residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) const {
    for (auto v : vertexSet)
        v->setVisited(false);
    s->setVisited(true);
    queue<Vertex *> q;
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
            f = min(f, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = min(f, e->getFlow());
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

bool Graph::relax(Vertex *u, Vertex *v, Edge *e) {
    if (v->getCost() > u->getCost() + e->getCost()) {
        v->setCost(u->getCost() + e->getCost());
        v->setPath(e);
        return true;
    }
    return false;
}
