//
// Created by manue on 03/04/2023.
//

#ifndef RAILWAY_VERTEX_H
#define RAILWAY_VERTEX_H


#include <string>
#include <vector>
#include "Edge.h"
#include "MutablePriorityQueue.h"

class Vertex {
public:
    /**
     * <br>Complexidade Temporal: O()
     * @param id
     * @param label
     */
    Vertex(int id, const std::string &label);

    /**
     * <br>Complexidade Temporal: O()
     * @param vertex
     * @return
     */
    bool operator<(Vertex & vertex) const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    int getId() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    const std::string &getLabel() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    std::vector<Edge *> getAdj() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    bool isVisited() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    bool isProcessing() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    unsigned getIndegree() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    unsigned getCost() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    Edge * getPath() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    std::vector<Edge *> getIncoming() const;

    /**
     * <br>Complexidade Temporal: O()
     * @param id
     */
    void setId(int id);

    /**
     * <br>Complexidade Temporal: O()
     * @param visited
     */
    void setVisited(bool visited);

    /**
     * <br>Complexidade Temporal: O()
     * @param processing
     */
    void setProcesssing(bool processing);

    /**
     * <br>Complexidade Temporal: O()
     * @param indegree
     */
    void setIndegree(unsigned indegree);

    /**
     * <br>Complexidade Temporal: O()
     * @param cost
     */
    void setCost(unsigned cost);

    /**
     * <br>Complexidade Temporal: O()
     * @param path
     */
    void setPath(Edge *path);

    /**
     * <br>Complexidade Temporal: O()
     * @param dest
     * @param capacity
     * @param service
     * @return
     */
    Edge * addEdge(Vertex *dest, unsigned capacity, Edge::Service service);

    /**
     * <br>Complexidade Temporal: O()
     * @param destID
     * @return
     */
    bool removeEdge(int destID);

    /**
     * <br>Complexidade Temporal: O()
     */
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;

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
    int queueIndex;

    /**
     * <br>Complexidade Temporal: O()
     * @param edge
     */
    void deleteEdge(Edge *edge) const;
};


#endif //RAILWAY_VERTEX_H
