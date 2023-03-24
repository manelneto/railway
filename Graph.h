//
// Created by manue on 15/03/2023.
//

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>



#include "Station.h"
#include "Segment.h"


class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Station *findVertex(const int &idStation) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addStationtoNet(const int &id);


    Station *findStation(const int &id) const;
    bool addStation(const int &id);
    bool addSegment(const int &sourc, const int &dest, unsigned int w, std::string service);
    bool addBidirectionalSegment(const int &sourc, const int &dest, unsigned int w, std::string service);
    int getNumstation() const;
    std::vector<Station *> getStationSet() const;


private:
    std::vector<Station *> stationSet;    // station set
protected:
    std::vector<Station *> StationSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const std::string a) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


#endif //RAILWAY_GRAPH_H
