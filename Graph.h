//
// Created by manue on 22/03/2023.
//

#ifndef RAILWAY_GRAPH_H
#define RAILWAY_GRAPH_H


#include <list>
#include <queue>
#include "Vertex.h"

class Graph {
public:
    /**
     * <br>Complexidade Temporal: O()
     * @param id
     * @return
     */
    Vertex *findVertex(const int &id) const;

    /**
     * <br>Complexidade Temporal: O()
     * @param id
     * @param label
     * @return
     */
    bool addVertex(const int &id, const std::string &label);

    /**
     * <br>Complexidade Temporal: O()
     * @param source
     * @param dest
     * @param capacity
     * @param service
     * @return
     */
    bool addEdge(const int &source, const int &dest, unsigned capacity, Edge::Service service) const;

    /**
     * <br>Complexidade Temporal: O()
     * @param source
     * @param dest
     * @param capacity
     * @param service
     * @return
     */
    bool addBidirectionalEdge(const int &source, const int &dest, unsigned capacity, Edge::Service service) const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    int getNumVertex() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    std::vector<Vertex *> getVertexSet() const;

    /**
     * <br>Complexidade Temporal: O()
     * @param source
     * @param target
     */
    void edmondsKarp(int source, int target) const;

    /**
     * <br>Complexidade Temporal: O()
     */
    void clear();

    /**
     * <br>Complexidade Temporal: O()
     * @param id
     * @return
     */
    unsigned getFlow(const int &id) const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    unsigned maxFlow() const;

    /**
     * <br>Complexidade Temporal: O()
     * @param pairs
     * @return
     */
    unsigned maxFlow(std::list<std::pair<std::string, std::string>> &pairs) const;

    /**
     * <br>Complexidade Temporal: O()
     * @param id
     */
    void addSuperSource(const int &id);

    /**
     * <br>Complexidade Temporal: O()
     */
    void removeSuperSource() const;

    /**
     * <br>Complexidade Temporal: O()
     * @param source
     * @param target
     * @return
     */
    bool removeEdge(const int &source, const int &target);

    /**
     * <br>Complexidade Temporal: O()
     * @param source
     */
    void dijkstra(int source) const;

    /**
     *
     * @param target
     * @return
     */
    unsigned getPathFlow(int target) const;

    /**
     *
     * @param target
     * @param flow
     * @return
     */
    unsigned getPathCost(int target, unsigned flow) const;

private:
    std::vector<Vertex *> vertexSet;

    /**
     *
     * @param id
     * @return
     */
    int findVertexIdx(const int &id) const;

    /**
     *
     * @param q
     * @param e
     * @param w
     * @param residual
     */
    static void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);

    /**
     *
     * @param s
     * @param t
     * @return
     */
    bool findAugmentingPath(Vertex *s, Vertex *t) const;

    /**
     *
     * @param s
     * @param t
     * @return
     */
    static unsigned findMinResidualAlongPath(Vertex *s, Vertex *t);

    /**
     *
     * @param s
     * @param t
     * @param f
     */
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, unsigned f);

    /**
     *
     * @param u
     * @param v
     * @param e
     * @return
     */
    static bool relax(Vertex *u, Vertex *v, Edge *e);
};


#endif //RAILWAY_GRAPH_H
