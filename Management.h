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
    bool menu();

private:
    std::unordered_set<Station, stationHash, stationHash> stations;
    Graph network;
    std::unordered_map<std::string, Graph> districts;
    std::unordered_map<std::string, Graph> municipalities;
    void readStationsFile(const std::string &filename, bool silent);
    void readNetworkFile(const std::string &filename, bool silent);
    static bool isInt(const std::string &str);
    static std::string readInput();
    static int readInt();
    static int validateInt(int n, int min, int max);
    Station readStation() const;
    void lerFicheirosDados(bool silent);
    void verificarFicheirosDados();
    void calcularFluxoMaximo(Graph &graph);
    void fluxoMaximoEspecifico();
    void fluxoMaximoGeral();
    void topNecessidades(std::list<std::pair<std::string,std::string>> pairs = {});
    void fluxoMaximoChegada();
    void custoMinimo();
    void conetividadeReduzida();
    void topAfetadas();
};


#endif //RAILWAY_MANAGEMENT_H
