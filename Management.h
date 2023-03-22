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
    Management();
    int menu();

private:
    std::unordered_set<Station, stationHash, stationHash> stations;
    Graph network;
    void readStationsFile();
    void readNetworkFile();
};


#endif //RAILWAY_MANAGEMENT_H
