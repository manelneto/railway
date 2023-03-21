//
// Created by manue on 15/03/2023.
//

#include "Graph.h"

int Graph::getNumstation() const {
    return stationSet.size();
}
std::vector<Station*> Graph::getStationSet() const {
    return stationSet;
}
Station* Graph::findStation(const int &id) const {
    for (auto station : stationSet)
        if (station->getId() == id)
            return station;
    return nullptr;
}
bool Graph::addStation(const int &id) {
    if (findStation(id) != nullptr)
        return false;
    stationSet.push_back(new Station(id));
    return true;
}
bool Graph::addSegment(const int &sourc, const int &dest, unsigned int w, Segment::Service service) {
    auto s1 = findStation(sourc);
    auto s2 = findStation(dest);
    if (s1 == nullptr || s2 == nullptr)
        return false;
    s1->addSegment(s2, w, service);
    return true;
}

bool Graph::addBidirectionalSegment(const int &sourc, const int &dest, unsigned int w, Segment::Service service) {
    auto v1 = findStation(sourc);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addSegment(v2, w,service);
    auto e2 = v2->addSegment(v1, w, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}
