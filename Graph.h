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
    /**@brief Procura o vértice do grafo pelo seu id.
     * 
     * Complexidade Temporal: O(V), sendo V o número de vértices do grafo
     * @param id id do vértice a procurar
     * @return apontador para o vértice encontrado
     */
    Vertex *findVertex(const int &id) const;

    /**@brief Adiciona ao grafo um vértice com id id e etiqueta label.
     * 
     * Complexidade Temporal: O(V), sendo V o número de vértices do grafo
     * @param id id do vértice a adicionar
     * @param label etiqueta do vértice a adicionar
     * @return true se a operação foi bem-sucedida, false caso contrário (já existia no grafo um vértice com o mesmo id)
     */
    bool addVertex(const int &id, const std::string &label);

    /**@brief Adiciona ao grafo uma aresta bidirecional (sob a forma de duas arestas simétricas) entre os vértices com id source e id dest, com capacidade capacity e serviço service.
     * 
     * Complexidade Temporal: O(V), sendo V o número de vértices do grafo
     * @param source id de um dos vértices da aresta a adicionar
     * @param dest id do outro vértice da aresta a adicionar
     * @param capacity capacidade da aresta a adicionar
     * @param service serviço da aresta a adicionar
     * @return true se a operação foi bem-sucedida, false caso contrário (não existe no grafo nenhum vértice com id source ou com id dest)
     */
    bool addBidirectionalEdge(const int &source, const int &dest, unsigned capacity, Edge::Service service) const;

    /**@brief Realiza o algoritmo de Edmonds-Karp para encontrar o caminho de fluxo máximo desde o vértice com id source até ao vértice com id target.
     * 
     * Complexidade Temporal: O(VE<SUP>2</SUP>), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @param source id do vértice de origem do caminho de fluxo máximo a encontrar
     * @param target id do vértice de destino do caminho de fluxo máximo a encontrar
     */
    void edmondsKarp(int source, int target) const;

    /**@brief Limpa o grafo, i. e., remove todas as suas arestas e todos os seus vértices.
     * 
     * Complexidade Temporal: O(V + E), sendo V o número de vértices do grafo e E o número de arestas do grafo
     */
    void clear();

    /**@brief Retorna o fluxo máximo que chega ao vértice com id id, depois de realizado o algoritmo de Edmonds-Karp.
     * 
     * Complexidade Temporal: O(V + E), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @param id id do vértice a analisar
     * @return fluxo máximo que chega ao vértice com id id
     */
    unsigned getFlow(const int &id) const;

    /**@brief Retorna a soma dos fluxos máximos entre todos os pares de vértices do grafo.
     * 
     * Complexidade Temporal: O(V<SUP>3</SUP>E<SUP>2</SUP>), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @return soma dos fluxos máximos entre todos os pares de vértices do grafo
     */
    unsigned sumFlow() const;

    /**@brief Retorna o maior fluxo máximo entre todos os pares de vértices do grafo e coloca em pairs as etiquetas dos pares de vértices entre os quais circula esse fluxo.
     * 
     * Complexidade Temporal: O(V<SUP>3</SUP>E<SUP>2</SUP>), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @param pairs lista a preencher com as etiquetas dos pares de vértices do grafo entre os quais circula o maior fluxo máximo entre todos os pares de vértices do grafo
     * @return maior fluxo máximo entre todos os pares de vértices do grafo
     */
    unsigned maxFlow(std::list<std::pair<std::string, std::string>> &pairs) const;

    /**@brief Adiciona ao grafo um vértice 'super source' (com id 0) e adiciona arestas com capacidade infinita desde esse vértice até todos os vértices com id diferente de id e grau de entrada igual a 1.
     * 
     * Complexidade Temporal: O(V), sendo V o número de vértices do grafo
     * @param id id do vértice ao qual, independentemente do grau de entrada, não ligar a 'super source'
     */
    void addSuperSource(const int &id);

    /**@brief Remove do grafo o vértice 'super source' (com id 0) e as arestas que dele partem.
     * 
     * Complexidade Temporal: O(V), sendo V o número de vértices do grafo
     */
    void removeSuperSource() const;

    /**@brief Remove do grafo a aresta entre os vértices com id source e id target.
     * 
     * Complexidade Temporal: O(V), sendo V o número de vértices do grafo
     * @param source id de um dos vértices da aresta a remover
     * @param target id do outro vértice da aresta a remover
     * @return true se a operação foi bem-sucedida, false caso contrário
     */
    bool removeEdge(const int &source, const int &target) const;

    /**@brief Realiza o algoritmo de Dijkstra para encontrar o caminho mais barato/curto desde o vértice com id source até todos os outros vértices do grafo.
     * 
     * Complexidade Temporal: O((V + E) log V), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @param source id do vértice de partida/origem do algoritmo de Dijkstra
     */
    void dijkstra(int source) const;

    /**@brief Determina o fluxo máximo até ao vértice com id target, seguindo o caminho determinado pelo algoritmo de Dijkstra e de acordo com o Teorema Maximum-Flow Minimum-Cut.
     * 
     * Complexidade Temporal: O(V + E), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @param target id do vértice de destino do caminho
     * @return fluxo máximo até ao vértice com id target, seguindo o caminho determinado pelo algoritmo de Dijkstra
     */
    unsigned getPathFlow(int target) const;

    /**@brief Determina o custo até ao vértice com id target, seguindo o caminho determinado pelo algoritmo de Dijkstra, passando por todas as arestas fluxo flow.
     * 
     * Complexidade Temporal: O(V + E), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @param target id do vértice de destino do caminho
     * @param flow fluxo a passar pelo caminho
     * @return custo até ao vértice com id target, seguindo o caminho determinado pelo algoritmo de Dijkstra, passando por todas as arestas fluxo flow
     */
    unsigned getPathCost(int target, unsigned flow) const;

private:
    std::vector<Vertex *> vertexSet;

    /**@brief Testa e visita o vértice w seguindo a aresta e, i. e., se o vértice w não estiver visitado e houver capacidade residual, visita o vértice w, define como seu predecessor a aresta e e coloca-o na fila q.
     * 
     * Complexidade Temporal: O(1)
     * @param q fila de apontadores para vértices
     * @param e aresta segundo a qual testar e visitar o vértice w
     * @param w vértice a testar e visitar
     * @param residual capacidade residual da aresta e
     */
    static void testAndVisit(std::queue<Vertex *> &q, Edge *e, Vertex *w, unsigned residual);

    /**@brief Procura um caminho de aumentação deste o vértice s até ao vértice t.
     * 
     * Complexidade Temporal: O(VE), sendo V o número de vértices do grafo e E o número de arestas do grafo
     * @param s vértice de origem
     * @param t vértice de destino
     * @return true se foi encontrado um caminho de aumentação desde o vértice s até ao vértice t, false caso contrário
     */
    bool findAugmentingPath(Vertex *s, Vertex *t) const;

    /**@brief Determina a menor capacidade residual entre o vértice s e o vértice t, seguindo o caminho de aumentação determinado anteriormente.
     * 
     * Complexidade Temporal: O(E), sendo E o número de arestas do grafo
     * @param s vértice de origem
     * @param t vértice de destino
     * @return menor capacidade residual entre o vértice s e o vértice t, seguindo o caminho de aumentação determinado anteriormente
     */
    static unsigned findMinResidualAlongPath(Vertex *s, Vertex *t);

    /**@brief Aumenta o fluxo entre o vértice s e o vértice t em f unidades de fluxo, seguindo o caminho de aumentação determinado anteriormente.
     * 
     * Complexidade Temporal: O(E), sendo E o número de arestas do grafo
     * @param s vértice de origem
     * @param t vértice de destino
     * @param f unidades de fluxo a aumentar
     */
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, unsigned f);

    /**@brief Relaxa a aresta e, desde o vértice u até ao vértice v, i. e., se o custo do vértice v for superior ao custo do vértice u somado com o custo da aresta e, atualiza o custo do vértice v para este segundo valor e atualiza o predecessor do vértice v para a aresta e.
     * 
     * Complexidade Temporal: O(1)
     * @param u vértice de origem da aresta e
     * @param v vértice de destino da aresta e
     * @param e aresta a relaxar
     * @return true se o relaxamento da aresta resultou num menor custo para o vértice v, false caso contrário
     */
    static bool relax(Vertex *u, Vertex *v, Edge *e);
};


#endif //RAILWAY_GRAPH_H
