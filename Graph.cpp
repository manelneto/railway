//
// Created by manue on 22/03/2023.
//

#include <stdexcept>
#include "Graph.h"
#include <climits>
#include "MutablePriorityQueue.h"
using namespace std;

Graph::~Graph() {
    deleteMatrix(distMatrix, (int) vertexSet.size());
    deleteMatrix(pathMatrix, (int) vertexSet.size());
}

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
    for (const auto edge : v1->getAdj())
        if (edge->getDest()->getId() == dest && edge->getCapacity() == capacity && edge->getService() == service)
            return false;
    auto e1 = v1->addEdge(v2, capacity, service);
    auto e2 = v2->addEdge(v1, capacity, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

int Graph::getNumVertex() const {
    return (int) vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::edmondsKarp(int source, int target) const {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw logic_error("Invalid source and/or target vertex");

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

unsigned Graph::maxFlow(list<pair<string, string>> &pairs) const {
    unsigned max = 0;
    for (const auto &u : vertexSet)
        for (const auto &v : vertexSet) {
            if (v->getId() <= u->getId())
                continue;
            edmondsKarp(u->getId(), v->getId());
            unsigned flow = getFlow(v->getId());
            // #include <iostream> std::cout << "O fluxo máximo entre " << u->getLabel() << " e " << v->getLabel() << " é " << flow << endl; // DEBUG ONLY
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
    // delete superSource;
}

int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return (int) i;
    return -1;
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

void Graph::testAndVisit(queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}
int Graph::dijsktra(int source, int target) const {
    const auto src= findVertex(source);
    unsigned max_capacity=UINT_MAX;
    src->setDist(0);
    src->setPath(nullptr);
    MutablePriorityQueue<Vertex> vertex_priorities;
    for (auto u : vertexSet){
        if (u!=src){
            u->setDist(INT_MAX);
            u->setPath(nullptr);
        }
        vertex_priorities.insert(u);

    }
    while(!vertex_priorities.empty()){
        Vertex* u = vertex_priorities.extractMin();

        for (Edge* e: u->getAdj()){
            int alt=0;
            Vertex* v = e->getDest();
            if (e->getService()==0) {
                alt= u->getDist()+ 2;
            }
            if (e->getService()==1) {
                alt= u->getDist()+ 4;
            }
            if (alt < v->getDist()){
                v->setDist(alt);
                v->setPath(e);
                vertex_priorities.decreaseKey(v);
            }
        }
    }
    const auto sink= findVertex(target);
    for(Edge* e= sink->getPath(); e!= nullptr; e= e->getOrig()->getPath()){
        if (e->getCapacity()< max_capacity){
            max_capacity=e->getCapacity();
        }
    }
    return max_capacity;

}
