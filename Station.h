//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_STATION_H
#define RAILWAY_STATION_H


#include <string>
#include "Segment.h"

class Station {
public:
    Station(const std::string &name, const std::string &district, const std::string &municipality,
            const std::string &township, const std::string &line, const int &id);
    Station(const int &id);

    const std::string &getName() const;

    const std::string &getDistrict() const;

    const std::string &getMunicipality() const;

    const std::string &getTownship() const;

    const std::string &getLine() const;

    const int &getId() const;

    Segment* addSegment(Station *dest, double w,std::string service);


    bool operator==(Station &s1);

private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
    int id;
};


#endif //RAILWAY_STATION_H
