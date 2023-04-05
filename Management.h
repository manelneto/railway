//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_MANAGEMENT_H
#define RAILWAY_MANAGEMENT_H


#include <unordered_set>
#include <unordered_map>
#include "Station.h"
#include "Graph.h"

class Management {
public:
    /**Apresenta o menu principal e permite selecionar uma das opções apresentadas.
     * <br>Complexidade Temporal: amplamente variável de acordo com o input
     * @return false se o utilizador pretender sair, true caso contrário
     */
    bool menu();

private:
    std::string stationsFile;
    std::string networkFile;
    bool filesRead = false;
    std::unordered_set<Station, stationHash, stationHash> stations;
    Graph network;
    std::unordered_map<std::string, Graph> districts;
    std::unordered_map<std::string, Graph> municipalities;

    /**Verifica se str é um número inteiro não negativo.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento de str
     * @param str string a verificar
     * @return true se str é um número inteiro não negativo, false caso contrário
     */
    static bool isInt(const std::string &str);

    /**Lê o input do utilizador.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento do input do utilizador
     * @return input do utilizador
     */
    static std::string readInput();

    /**Lê o input do utilizador, forçando a que seja um número inteiro não negativo.
     * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
     * @return número inteiro não negativo introduzido pelo utilizador
     */
    static int readInt();

    /**Valida um número inteiro, isto é, verifica se n pertence ao intervalo [min, max]. Enquanto o número for inválido, tenta ler um número válido.
     * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
     * @param n número a validar
     * @param min limite inferior do intervalo de números válidos
     * @param max limite superior do intervalo de números válidos
     * @return número inteiro válido introduzido pelo utilizador
     */
    static int validateInt(int n, int min, int max);

    /**Lê uma estação através do seu nome introduzido pelo utilizador, forçando a que ela exista.
     * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
     * @return estação existente introduzida pelo utilizador
     */
    Station readStation() const;

    /**Lê um segmento através dos nomes das estações de origem e de destino introduzidos pelo utilizador, forçando a que ele exista e seja direto entre as duas estações. Remove esse segmento da rede.
     * <br>Complexidade Temporal: O(nV), sendo n a posição do primeiro input válido introduzido pelo utilizador e V o número de vértices do grafo da rede
     */
    void removeSegment() const;

    /**Lê o ficheiro de estações e cria as tabelas de dispersão de estações, de distritos e de municípios e os nós do grafo da rede.
     * <br>Complexidade Temporal: O(nV), sendo n o número de linhas do ficheiro de estações e V o número de vértices do grafo da rede
     * @param silent indica se a função deve ser silenciosa (true) ou imprimir mensagens de sucesso/insucesso (false)
     * @return true se a leitura do ficheiro de estações foi bem-sucedida, false caso contrário
     */
    bool readStationsFile(bool silent);

    /**Lê o ficheiro da rede e preenche os grafos da rede, dos distritos e dos municípios com os segmentos.
     * <br>Complexidade Temporal: O(nV), sendo n o número de linhas do ficheiro de estações e V o número de vértices do grafo da rede
     * @param silent indica se a função deve ser silenciosa (true) ou imprimir mensagens de sucesso/insucesso (false)
     * @return true se a leitura do ficheiro da rede foi bem-sucedida, false caso contrário
     */
    bool readNetworkFile(bool silent);

    /**Lê os ficheiros de dados, depois de limpar os dados anteriores.
     * <br>Complexidade Temporal: O(nV), sendo n o número de linhas do ficheiro de estações e V o número de vértices do grafo da rede
     * @param silent indica se a função deve ser silenciosa (true) ou imprimir mensagens de sucesso/insucesso (false)
     */
    void lerFicheirosDados(bool silent);

    /**Verifica se os ficheiros de dados foram lidos, i. e., se existem dados para analisar. Em caso negativo, lê os ficheiros de dados.
     * <br>Complexidade Temporal: O(nV), sendo n o número de linhas do ficheiro de estações e V o número de vértices do grafo da rede
     */
    void verificarFicheirosDados();

    /**Calcula o fluxo máximo no grafo graph entre duas estações lidas do utilizador.
     * <br>Complexidade Temporal: O(VE<SUP>2</SUP>), sendo V o número de vértices do grafo graph e E o número de arestas do grafo graph
     * @param graph grafo a analisar
     */
    void calcularFluxoMaximo(Graph &graph);

    /**Calcula o número máximo de comboios que podem viajar simultaneamente entre duas estações lidas do utilizador.
     * <br>Complexidade Temporal: O(VE<SUP>2</SUP>), sendo V o número de vértices do grafo da rede e E o número de arestas do grafo da rede
     */
    void fluxoMaximoEspecifico();

    /**Determina, de entre todos pares de estações, quais os que requerem o maior número de comboios.
     * <br>Complexidade Temporal: O(V<SUP>3</SUP>E<SUP>2</SUP>), sendo V o número de vértices do grafo da rede e E o número de arestas do grafo da rede
     */
    void fluxoMaximoGeral();

    /**Reporta o top K (lido do utilizador) de municípios e distritos tendo em conta as suas necessidades de transportes.
     * <br>Complexidade Temporal: O(V<SUP>3</SUP>E<SUP>2</SUP>), sendo V o número de vértices do grafo da rede e E o número de arestas do grafo da rede
     */
    void topNecessidades();

    /**Reporta o número máximo de comboios que podem chegar simultaneamente a uma dada estação lida do utilizador.
     * <br>Complexidade Temporal: O(VE<SUP>2</SUP>), sendo V o número de vértices do grafo da rede e E o número de arestas do grafo da rede
     */
    void fluxoMaximoChegada();

    /**Calcula o número máximo de comboios que podem viajar simultaneamente entre duas estações lidas do utilizador com custo mínimo.
     * <br>Complexidade Temporal: O((V + E) log V), sendo V o número de vértices do grafo da rede E o número de arestas do grafo da rede
     */
    void custoMinimo();

    /**Calcula o número máximo de comboios que podem viajar simultaneamente entre duas estações lidas do utilizador com conetividade reduzida, removendo segmentos lidos do utilizador.
     * <br>Complexidade Temporal: O(VE<SUP>2</SUP>), sendo V o número de vértices do grafo da rede e E o número de arestas do grafo da rede
     */
    void conetividadeReduzida();

    /**Reporta o top K (lido do utilizador) de estações mais afetadas por uma falha num segmento lido do utilizador.
     * <br>Complexidade Temporal: O(V<SUP>2</SUP>E<SUP>2</SUP>), sendo V o número de vértices do grafo da rede (deve coincidir com o tamanho de stations) e E o número de arestas do grafo da rede
     */
    void topAfetadas();
};


#endif //RAILWAY_MANAGEMENT_H
