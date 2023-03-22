//
// Created by manue on 15/03/2023.
//

#include "Management.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Management::Management() {
    readStationsFile();
    readNetworkFile();
}

void Management::readStationsFile() {
    ifstream in("../files/stations.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro stations.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string fileLine;
    getline(in, fileLine);
    int id = 1;
    while (getline(in, fileLine)) {
        istringstream iss(fileLine);
        string field;
        vector<string> fields(6);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        string name = fields[0];
        string district = fields[1];
        string municipality = fields[2];
        string township = fields[3];
        string line = fields[4];
        Station station = Station(name, district, municipality, township, line, id++);
        stations.insert(station);

    }
    cout << "Leitura de ficheiro stations.csv bem-sucedida." << endl;
}

void Management::readNetworkFile() {
    ifstream in("../files/network.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro network.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(4);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        auto stationA = stations.find(Station(fields[0]));
        auto stationB = stations.find(Station(fields[1]));
        unsigned capacity = stoi(fields[2]);
        Edge::Service service = fields[3] == "STANDARD" ? Edge::STANDARD : Edge::ALFA;
    }
    cout << "Leitura de ficheiro network.csv bem-sucedida." << endl;
}
