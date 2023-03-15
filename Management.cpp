//
// Created by manue on 15/03/2023.
//

#include "Management.h"
#include "Station.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector> //???

using namespace std;

void Management::readStationsFile() {
    ifstream in("../files/stations.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro stations.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string fileLine;
    getline(in, fileLine);
    int number = 1;
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
        Station station = Station(name, district, municipality, township, line);
    }
    cout << "Leitura de ficheiro stations.csv bem-sucedida." << endl;
}
