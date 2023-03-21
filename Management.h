//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_MANAGEMENT_H
#define RAILWAY_MANAGEMENT_H


#include <unordered_map>
#include "unordered_map"

#include "Station.h"

using namespace std;

class Management {
public:
    Management();

private:
    void readNetwork();
    void readStationsFile();
    unordered_map<string, Station> stationsbyName;
    unordered_map<string, int> stationIDs;
    unordered_map<string, unordered_map<string, unordered_map<string, Station>>> stationsByDistrict;
};


#endif //RAILWAY_MANAGEMENT_H
