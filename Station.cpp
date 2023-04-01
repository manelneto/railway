//
// Created by manue on 15/03/2023.
//

#include "Station.h"
#include <iostream>

using namespace std;

string Station::sanitize(const string &str) {
    string sanitized;
    for (const char &ch : str)
        if (isalpha(ch) || isdigit(ch) || isspace(ch) || ispunct(ch))
            sanitized += (char) toupper(ch);
    return sanitized;
}

Station::Station() {}

Station::Station(const std::string &name) : sanitizedName(sanitize(name)) {}

Station::Station(const std::string &name, const std::string &district, const std::string &municipality, const std::string &township, const std::string &line, int id) : sanitizedName(sanitize(name)), name(name), district(district), municipality(municipality), township(township), line(line), id(id) {}

const std::string &Station::getSanitizedName() const {
    return sanitizedName;
}

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

int Station::getId() const {
    return id;
}

bool Station::operator==(const Station &rhs) const {
    return sanitizedName == rhs.sanitizedName;
}

void Station::print() const {
    cout << "Estação " << name;
    if (!district.empty())
         cout << " (" << district << "; " << municipality << "; " << township << ")";
    cout << " - " << line;
}
