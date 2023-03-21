//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_GRAPH_H
#define RAILWAY_GRAPH_H


#include <vector>
#include "Station.h"
#include "Segment.h"

class Graph {
public:

    Station *findStation(const int &id) const;
    bool addStation(const int &id);
    bool addSegment(const int &sourc, const int &dest, unsigned int w, Segment::Service service);
    bool addBidirectionalSegment(const int &sourc, const int &dest, unsigned int w, Segment::Service service);
    int getNumstation() const;
    std::vector<Station *> getStationSet() const;

private:
    std::vector<Station *> stationSet;    // station set


};



#endif //RAILWAY_GRAPH_H
