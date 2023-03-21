//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_SEGMENT_H
#define RAILWAY_SEGMENT_H


#include "Station.h"

class Segment {
public:
    enum Services {STANDARD, ALFA};

    Segment(const Station &stationA, const Station &stationB, unsigned int capacity, std::string service);


    const Station &getStationA() const;

    const Station &getStationB() const;

    unsigned int getCapacity() const;

    Services getService() const;

private:
    Station StationA;
    Station StationB;
    unsigned int capacity;
    enum Services services;
    bool selected=false;
    Segment * reverse= nullptr;
    std::string service;
};


#endif //RAILWAY_SEGMENT_H
