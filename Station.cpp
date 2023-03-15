//
// Created by manue on 15/03/2023.
//

#include "Station.h"

Station::Station(const std::string &name, const std::string &district, const std::string &municipality, const std::string &township, const std::string &line)
    : name(name), district(district), municipality(municipality), township(township), line(line) {}

const std::string &Station::getName() const {
    return name;
}

const std::string &Station::getDistrict() const {
    return district;
}

const std::string &Station::getMunicipality() const {
    return municipality;
}

const std::string &Station::getTownship() const {
    return township;
}

const std::string &Station::getLine() const {
    return line;
}
