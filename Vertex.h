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
    /**Construtor com parâmetros. Constrói um vértice com id id e etiqueta label.
     * <br>Complexidade Temporal: O(1)
     * @param id id
     * @param label etiqueta
     */
    Vertex(int id, const std::string &label);

    /**Compara o vértice e vertex quando ao seu custo.
     * <br>Complexidade Temporal: O(1)
     * @param vertex vértice com o qual comparar
     * @return true se o custo do vértice é inferior ao de vertex, false caso contrário
     */
    bool operator<(Vertex & vertex) const;

    /**Retorna o id do vértice
     * <br>Complexidade Temporal: O(1)
     * @return id do vértice
     */
    int getId() const;

    /**Retorna a etiqueta do vértice
     * <br>Complexidade Temporal: O(1)
     * @return etiqueta do vértice
     */
    const std::string &getLabel() const;

    /**Retorna a lista de adjacências (arestas a sair) do vértice
     * <br>Complexidade Temporal: O(1)
     * @return lista de adjacências (arestas a sair) do vértice
     */
    std::vector<Edge *> getAdj() const;

    /**Indica se o vértice foi visitado.
     * <br>Complexidade Temporal: O(1)
     * @return true se o vértice foi visitado, false caso contrário
     */
    bool isVisited() const;

    /**Retorna o grau de entrada do vértice.
     * <br>Complexidade Temporal: O(1)
     * @return grau de entrada do vértice
     */
    unsigned getIndegree() const;

    /**Retorna o custo do vértice
     * <br>Complexidade Temporal: O(1)
     * @return custo do vértice
     */
    unsigned getCost() const;

    /**Retorna a aresta predecessora do vértice no caminho atual
     * <br>Complexidade Temporal: O(1)
     * @return a aresta predecessora do vértice no caminho atual
     */
    Edge * getPath() const;

    /**Retorna as arestas a entrar no vértice.
     * <br>Complexidade Temporal: O(1)
     * @return arestas a entrar no vértice
     */
    std::vector<Edge *> getIncoming() const;

    /**Define estado visitado do vértice como visited.
     * <br>Complexidade Temporal: O(1)
     * @param visited novo estado visitado do vértice
     */
    void setVisited(bool visited);

    /**Define o grau de entrada do vértice como indegree.
     * <br>Complexidade Temporal: O(1)
     * @param indegree novo grau de entrada do vértice
     */
    void setIndegree(unsigned indegree);

    /**Define o custo do vértice como cost.
     * <br>Complexidade Temporal: O(1)
     * @param cost novo custo do vértice
     */
    void setCost(unsigned cost);

    /**Define a aresta predecessora do vértice como path.
     * <br>Complexidade Temporal: O(1)
     * @param path nova aresta predecessora do vértice
     */
    void setPath(Edge *path);

    /**Adiciona um aresta desde o vértice até dest, com capacidade capacity e serviço service.
     * <br>Complexidade Temporal: O(1)
     * @param dest destino da aresta
     * @param capacity capacidade da aresta
     * @param service serviço da aresta
     * @return aresta adicionada ao vértice
     */
    Edge * addEdge(Vertex *dest, unsigned capacity, Edge::Service service);

    /**Remove do vértice a aresta com destino ao vértice cujo id é destID.
     * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências (arestas a sair) do vértice
     * @param destID id do vértice de destino da aresta a remover
     * @return true se a aresta foi encontrada e removida, false caso contrário
     */
    bool removeEdge(int destID);

    /**Remove todas as arestas de saída do vértice.
     * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de adjacências (arestas a sair) do vértice
     */
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;

private:
    int id;
    std::string label;
    std::vector<Edge *> adj;
    bool visited = false;
    unsigned indegree = 0;
    unsigned cost = 0;
    Edge * path = nullptr;
    std::vector<Edge *> incoming;
    int queueIndex;

    /**Apaga a aresta edge.
     * <br>Complexidade Temporal: O(n), sendo n o tamanho da lista de arestas de entrada no vértice de destino da aresta edge.
     * @param edge aresta a apagar
     */
    void deleteEdge(Edge *edge) const;
};


#endif //RAILWAY_VERTEX_H
