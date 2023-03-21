//
// Created by manue on 15/03/2023.
//

#include "Management.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>//???
#include "Station.h"
#include "Segment.h"

using namespace std;
Management::Management() {readStationsFile();
readNetwork();}
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
        stationsbyName.insert({station.getName(),station});
    }
    cout << "Leitura de ficheiro stations.csv bem-sucedida." << endl;
}
void Management::readNetwork() {
    readStationsFile();
    ifstream in("../files/network.csv");
    int i=0;
    string line;
    getline(in,line);

    while (getline(in,line)){
        string Station_A,Station_B,Capacity,Service;

        istringstream iss(line);
        while(iss.good()){
            string substr;
            getline(iss, substr, ',');
            if (i == 0)
                Station_A = substr;
            if (i == 1)
                Station_B = substr;
            if (i == 2)
                Capacity = substr;
            if (i == 3)
                Service= substr;
            i++;
        }
        unsigned int capacity= stoi(Capacity);
        i=0;
        Segment new_segment=Segment(stationsbyName.at(Station_A), stationsbyName.at(Station_B), capacity, Service);
    }
}


