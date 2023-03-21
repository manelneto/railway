//
// Created by manue on 15/03/2023.
//

#include "Segment.h"

Segment::Segment(const Station &stationA, const Station &stationB, unsigned int capacity, std::string service)
        : StationA(stationA), StationB(stationB), capacity(capacity), service(service) {}

const Station &Segment::getStationA() const {
    return StationA;
}

const Station &Segment::getStationB() const {
    return StationB;
}

unsigned int Segment::getCapacity() const {
    return capacity;
}

std::string Segment::getService() const {
    return service;
}
