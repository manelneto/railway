//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_MANAGEMENT_H
#define RAILWAY_MANAGEMENT_H


#include <unordered_set>
#include "Station.h"
#include "Graph.h"

class Management {
public:
    bool menu();

private:
    std::unordered_set<Station, stationHash, stationHash> stations;
    Graph network;
    void readStationsFile(const std::string &filename);
    void readNetworkFile(const std::string &filename);
    static bool isInt(const std::string &str);
    static std::string readInput();
    static int readInt();
    static int validateInt(int n, int min, int max);
    Station readStation() const;
    void lerFicheirosDados();
    void verificarFicheirosDados();
    void fluxoMaximoEspecifico();
    void fluxoMaximoGeral();
    void topNecessidades();
    void fluxoMaximoChegada();
    void custoMinimo();
    void conetividadeReduzida();
    void topAfetadas();
};


#endif //RAILWAY_MANAGEMENT_H
