//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_STATION_H
#define RAILWAY_STATION_H


#include <string>

class Station {
public:
    Station();
    Station(const std::string &name);
    Station(const std::string &name, const std::string &district, const std::string &municipality, const std::string &township, const std::string &line, int id);
    const std::string &getSanitizedName() const;
    const std::string &getName() const;
    const std::string &getDistrict() const;
    const std::string &getMunicipality() const;
    const std::string &getTownship() const;
    const std::string &getLine() const;
    int getId() const;
    bool operator==(const Station &rhs) const;
    void print() const;

private:
    std::string sanitizedName;
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
    int id;
    static std::string sanitize(const std::string &str);
};

struct stationHash {
    int operator()(const Station &station) const {
        const std::string& str = station.getSanitizedName();
        int v = 0;
        for (const char &ch : str)
            v = 37*v + ch;
        return v;
    }

    bool operator()(const Station &station1, const Station &station2) const {
        return station1 == station2;
    }
};

#endif //RAILWAY_STATION_H
