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
    /**
     * <br>Complexidade Temporal: O()
     * @return
     */
    bool menu();

private:
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

    /**
     *
     * @return
     */
    Station readStation() const;

    /**
     *
     */
    void removeSegment() const;

    /**
     * <br>Complexidade Temporal: O()
     * @param filename
     * @param silent
     */
    void readStationsFile(const std::string &filename, bool silent);

    /**
     * <br>Complexidade Temporal: O()
     * @param filename
     * @param silent
     */
    void readNetworkFile(const std::string &filename, bool silent);

    /**
     * <br>Complexidade Temporal: O()
     * @param silent
     */
    void lerFicheirosDados(bool silent);

    /**
     * <br>Complexidade Temporal: O()
     */
    void verificarFicheirosDados();

    /**
     * <br>Complexidade Temporal: O()
     * @param graph
     */
    void calcularFluxoMaximo(Graph &graph);

    /**
     * <br>Complexidade Temporal: O()
     */
    void fluxoMaximoEspecifico();

    /**
     * <br>Complexidade Temporal: O()
     */
    void fluxoMaximoGeral();

    /**
     * <br>Complexidade Temporal: O()
     */
    void topNecessidades();

    /**
     * <br>Complexidade Temporal: O()
     */
    void fluxoMaximoChegada();

    /**
     * <br>Complexidade Temporal: O()
     */
    void custoMinimo();

    /**
     * <br>Complexidade Temporal: O()
     */
    void conetividadeReduzida();

    /**
     * <br>Complexidade Temporal: O()
     */
    void topAfetadas();
};


#endif //RAILWAY_MANAGEMENT_H
