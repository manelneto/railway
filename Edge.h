//
// Created by manue on 03/04/2023.
//

#ifndef RAILWAY_EDGE_H
#define RAILWAY_EDGE_H


class Vertex;

class Edge {
public:
    enum Service {
        STANDARD, ALFA, OTHER
    };

    /**@brief Construtor com parâmetros. Constrói uma aresta com origem orig, destino dest, capacidade capacity, serviço service e custo de acordo com o serviço (2€ para STANDARD, 4€ para ALFA e -1€ para OTHER).
     * 
     * Complexidade Temporal: O(1)
     * @param orig origem
     * @param dest destino
     * @param capacity capacidade
     * @param service serviço
     */
    Edge(Vertex *orig, Vertex *dest, unsigned capacity, Service service);

    /**@brief Retorna a origem da aresta.
     * 
     * Complexidade Temporal: O(1)
     * @return origem da aresta
     */
    Vertex *getOrig() const;

    /**@brief Retorna o destino da aresta.
     * 
     * Complexidade Temporal: O(1)
     * @return destino da aresta
     */
    Vertex *getDest() const;

    /**@brief Retorna a capacidade da aresta.
     * 
     * Complexidade Temporal: O(1)
     * @return capacidade da aresta
     */
    unsigned getCapacity() const;

    /**@brief Retorna o serviço da aresta.
     * 
     * Complexidade Temporal: O(1)
     * @return serviço da aresta
     */
    Service getService() const;

    /**@brief Retorna o custo da aresta.
     * 
     * Complexidade Temporal: O(1)
     * @return custo da aresta
     */
    unsigned getCost() const;

    /**@brief Retorna o fluxo que passa pela aresta.
     * 
     * Complexidade Temporal: O(1)
     * @return fluxo que passa pela aresta
     */
    unsigned getFlow() const;

    /**@brief Define o fluxo que passa pela aresta como flow.
     * 
     * Complexidade Temporal: O(1)
     * @param flow novo fluxo a passar pela aresta
     */
    void setFlow(unsigned flow);

private:
    Vertex *orig;
    Vertex *dest;
    unsigned capacity;
    Service service;
    unsigned cost;
    unsigned flow = 0;
};


#endif //RAILWAY_EDGE_H
