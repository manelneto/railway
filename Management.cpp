//
// Created by manue on 15/03/2023.
//

#include "Management.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/**Verifica se str é um número inteiro não negativo.
 * <br>Complexidade Temporal: O(n), sendo n o comprimento de str
 * @param str string a verificar
 * @return true se str é um número inteiro não negativo, false caso contrário
 */
bool Management::isInt(const string &str) {
    for (const char &ch : str)
        if (!isdigit(ch))
            return false;
    return true;
}

/**Lê o input do utilizador.
 * <br>Complexidade Temporal: O(n), sendo n o comprimento do input do utilizador
 * @return input do utilizador
 */
string Management::readInput() {
    string s;
    getline(cin, s);
    cout << endl;
    return s;
}

/**Lê o input do utilizador, forçando a que seja um número inteiro não negativo.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return número inteiro não negativo introduzido pelo utilizador
 */
int Management::readInt() {
    string s = readInput();
    while (!isInt(s)) {
        cout << "Deve inserir um número inteiro não negativo. Tente novamente: ";
        s = readInput();
    }
    int n = stoi(s);
    return n;
}

/**Valida um número inteiro, isto é, verifica se n pertence ao intervalo [min, max]. Enquanto o número for inválido, tenta ler um número válido.
 * <br>Complexidade Temporal: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @param n número a validar
 * @param min limite inferior do intervalo de números válidos
 * @param max limite superior do intervalo de números válidos
 * @return número inteiro válido introduzido pelo utilizador
 */
int Management::validateInt(int n, int min, int max) {
    while (n < min || n > max) {
        cout << "O número inserido não é válido (deve pertencer ao intervalo [" << min << ", " << max << "]). Tente novamente: ";
        n = readInt();
    }
    return n;
}

Station Management::readStation() const {
    cout << "Nome da Estação: ";
    string name = readInput();
    Station station = Station(name);
    while (stations.find(station) == stations.end()) {
        cout << "Estação não encontrada. Tente novamente." << endl;
        station = readStation();
    }
    return  *stations.find(station);
}

bool Management::menu() {
    cout << "\nMenu Principal:\n"
            "1 - Ler ficheiros de dados\n"
            "2 - Calcular o número máximo de comboios que podem viajar simultaneamente entre duas estações\n"
            "3 - Determinar, de entre todos pares de estações, quais os que requerem o maior número de comboios\n"
            "4 - Reportar o top K de municípios e distritos tendo em conta as suas necessidades de transportes\n"
            "5 - Reportar o número máximo de comboios que podem chegar simultaneamente a uma dada estação\n"
            "6 - Calcular o número máximo de comboios que podem viajar simultaneamente entre duas estações com custo mínimo\n"
            "7 - Calcular o número máximo de comboios que podem viajar simultaneamente entre duas estações com conetividade reduzida\n"
            "8 - Reportar o top K de estações mais afetadas por uma falha num segmento\n"
            "0 - Sair\n"
            "Opção: ";
    int option = readInt();
    option = validateInt(option, 0, 8);
    if (option == 1)
        lerFicheirosDados();
    else if (option == 2)
        fluxoMaximoEspecifico();
    else if (option == 3)
        fluxoMaximoGeral();
    else if (option == 4)
        topNecessidades();
    else if (option == 5)
        fluxoMaximoChegada();
    else if (option == 6)
        custoMinimo();
    else if (option == 7)
        conetividadeReduzida();
    else if (option == 8)
        topAfetadas();
    else
        return false;
    return true;
}

void Management::readStationsFile() {
    ifstream in("../files/stations.csv");
    if (!in.is_open()) {
        cout << "\nErro ao abrir o ficheiro stations.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string fileLine;
    getline(in, fileLine);
    int id = 1;
    unsigned ignored = 0;
    while (getline(in, fileLine)) {
        istringstream iss(fileLine);
        string field;
        vector<string> fields(6);
        unsigned f = 0;
        bool escape = false;
        while (getline(iss, field, ',')) {
            if (field[0] == '"' && field[field.length() - 1] != '"') {
                fields[f] = field.substr(1, field.length() - 1);
                fields[f] += ",";
                escape = true;
                continue;
            } else if (field[field.length() - 1] == '"' && field[0] != '"') {
                field = field.substr(0, field.length() - 1);
                escape = false;
            }
            if (escape) {
                fields[f] += field;
                fields[f] += ",";
            }
            else
                fields[f++] += field;
        }
        string name = fields[0];
        string district = fields[1];
        string municipality = fields[2];
        string township = fields[3];
        string line = fields[4];
        Station station = Station(name, district, municipality, township, line, id);
        if (stations.insert(station).second) {
            network.addVertex(id++);
            // station.print(); // DEBUG ONLY
        } else
            ignored++;
    }
    cout << "\nLeitura do ficheiro stations.csv bem-sucedida." << endl;
    cout << "Foram lidas " << stations.size() << " estações e foram ignoradas " << ignored << " estações por serem duplicadas (estações com o mesmo nome)." << endl;
}

void Management::readNetworkFile() {
    ifstream in("../files/network.csv");
    if (!in.is_open()) {
        cout << "\nErro ao abrir o ficheiro network.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    string line;
    getline(in, line);
    unsigned counter = 0;
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
        if (stationA != stations.end() && stationB != stations.end()) {
            network.addBidirectionalEdge(stationA->getId(), stationB->getId(), capacity, service);
            counter++;
        }
    }
    cout << "\nLeitura do ficheiro network.csv bem-sucedida." << endl;
    cout << "Foram lidos " << counter << " segmentos." << endl;
}

void Management::lerFicheirosDados() {
    stations.clear();
    readStationsFile();
    readNetworkFile();
    cout << "\nO grafo da rede tem " << network.getNumVertex() << " nós/vértices (estações)." << endl; // DEBUG ONLY
}

void Management::fluxoMaximoEspecifico() {
    // TODO
}

void Management::fluxoMaximoGeral() {
    // TODO
}

void Management::topNecessidades() {
    // TODO
}

void Management::fluxoMaximoChegada() {
    // TODO
}

void Management::custoMinimo() {
    // TODO
}

void Management::conetividadeReduzida() {
    // TODO
}

void Management::topAfetadas() {
    // TODO
}
