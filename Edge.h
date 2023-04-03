//
// Created by manue on 03/04/2023.
//

#ifndef RAILWAY_EDGE_H
#define RAILWAY_EDGE_H


class Vertex;

class Edge {
public:
    enum Service {STANDARD, ALFA, OTHER};

    /**
     * <br>Complexidade Temporal: O()
     * @param orig
     * @param dest
     * @param capacity
     * @param service
     */
    Edge(Vertex *orig, Vertex *dest, unsigned capacity, Service service);

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    Vertex * getOrig() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    Vertex * getDest() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    unsigned getCapacity() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    Service getService() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    unsigned getCost() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    unsigned getFlow() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    bool isSelected() const;

    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    Edge * getReverse() const;

    /**
     * <br>Complexidade Temporal: O()
     * @param flow
     */
    void setFlow(unsigned flow);

    /**
     * <br>Complexidade Temporal: O()
     * @param selected
     */
    void setSelected(bool selected);

    /**
     * <br>Complexidade Temporal: O()
     * @param reverse
     */
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
