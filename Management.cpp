//
// Created by manue on 15/03/2023.
//

#include "Management.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

bool Management::isInt(const string &str) {
    for (const char &ch : str)
        if (!isdigit(ch))
            return false;
    return true;
}

string Management::readInput() {
    string s;
    getline(cin, s);
    cout << endl;
    return s;
}

int Management::readInt() {
    string s = readInput();
    while (!isInt(s)) {
        cout << "Deve inserir um número inteiro não negativo. Tente novamente: ";
        s = readInput();
    }
    int n = stoi(s);
    return n;
}

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

void Management::removeSegment() const {
    cout << "Estação A" << endl;
    Station source = readStation();
    cout << "Estação B" << endl;
    Station target = readStation();
    if (!network.removeEdge(source.getId(), target.getId())) {
        cout << "Não existe nenhum segmento que ligue diretamente " << source.getName() << " e " << target.getName() << ". Tente novamente." << endl;
        removeSegment();
    }
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
        lerFicheirosDados(false);
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

void Management::readStationsFile(bool silent) {
    ifstream in("../files/" + stationsFile);
    if (!in.is_open() && !silent) {
        cout << "Erro ao abrir o ficheiro " << stationsFile << "." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    if (!silent)
        cout << "A ler ficheiro " << stationsFile << "..." << endl;
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
            network.addVertex(id, name);
            if (!district.empty())
                districts[district].addVertex(id, name);
            if (!municipality.empty())
                municipalities[municipality].addVertex(id, name);
            id++;
        }
        else
            ignored++;
    }
    if (!silent) {
        cout << "Leitura do ficheiro " << stationsFile << " bem-sucedida!" << endl;
        cout << "Foram lidas " << stations.size() << " estações e foram ignoradas " << ignored << " estações por serem duplicadas (estações com o mesmo nome)." << endl;
    }
}

void Management::readNetworkFile(bool silent) {
    ifstream in("../files/" + networkFile);
    if (!in.is_open() && !silent) {
        cout << "Erro ao abrir o ficheiro " << networkFile << "." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório files." << endl;
        return;
    }
    if (!silent)
        cout << "A ler ficheiro " << networkFile << "..." << endl;
    string line;
    getline(in, line);
    unsigned counter = 0;
    unsigned error = 0;
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
            if (!network.addBidirectionalEdge(stationA->getId(), stationB->getId(), capacity, service))
                error++;
            if (stationA->getDistrict() == stationB->getDistrict())
                districts[stationA->getDistrict()].addBidirectionalEdge(stationA->getId(), stationB->getId(), capacity, service);
            if (stationA->getMunicipality() == stationB -> getMunicipality())
                municipalities[stationA->getMunicipality()].addBidirectionalEdge(stationA->getId(), stationB->getId(), capacity, service);
            counter++;
        } else
            error++;
    }
    if (!silent) {
        cout << "Leitura do ficheiro " << networkFile << " bem-sucedida!" << endl;
        cout << "Foram lidos " << counter << " segmentos e ocorreram " << error << " erros (estações de origem/destino não encontradas ou ligações duplicadas)." << endl;
    }
}

void Management::lerFicheirosDados(bool silent) {
    stations.clear();
    network.clear();
    if (!silent) {
        cout << "Nome do ficheiro de estações (stations*.csv): ";
        stationsFile = readInput();
        cout << "Nome do ficheiro de rede (network*.csv): ";
        networkFile = readInput();
    }
    readStationsFile(silent);
    if (!silent)
        cout << endl;
    readNetworkFile(silent);
    if (!silent)
        cout << endl;
}

void Management::verificarFicheirosDados() {
    if (network.getNumVertex() == 0) {
        cout << "Ainda não leu os ficheiros de dados, pelo que não existe nenhum grafo para analisar." << endl;
        lerFicheirosDados(false);
    }
}

void Management::calcularFluxoMaximo(Graph &graph) {
    cout << "Estação A" << endl;
    Station source = readStation();
    cout << "Estação B" << endl;
    Station target = readStation();
    network.edmondsKarp(source.getId(), target.getId());
    unsigned flow = network.getFlow(target.getId());
    if (flow == 0)
        cout << "Não é possível viajar entre " << source.getName() << " e " << target.getName() << endl;
    else
        cout << "O número máximo de comboios que podem viajar simultaneamente entre " << source.getName() << " e " << target.getName() << " é " << flow << endl;
}

void Management::fluxoMaximoEspecifico() {
    verificarFicheirosDados();
    calcularFluxoMaximo(network);
}

void Management::fluxoMaximoGeral() {
    verificarFicheirosDados();
    cout << "A calcular..." << endl;
    list<pair<string, string>> pares;
    cout << endl;
    unsigned max = network.maxFlow(pares);
    cout << "Os pares de estações que requerem o maior número de comboios (" << max << ") são:" << endl;
    for (const auto &par : pares) {
        auto stationA = stations.find(Station(par.first));
        if (stationA != stations.end())
            stationA->print();
        cout << " & ";
        auto stationB = stations.find(Station(par.second));
        if (stationB != stations.end())
            stationB->print();
        cout << endl;
    }
}

void Management::topNecessidades() {
    verificarFicheirosDados();
    cout << "Introduza o valor de K (0 para um top completo, com todos os municípios e distritos): ";
    unsigned k = readInt();
    priority_queue<pair<unsigned, string>> topDistritos;
    priority_queue<pair<unsigned, string>> topMunicipios;
    for (const auto &district : districts)
        topDistritos.push(make_pair(district.second.sumFlow(), district.first));
    for (const auto &municipality : municipalities)
        topMunicipios.push(make_pair(municipality.second.sumFlow(), municipality.first));
    unsigned m = k == 0 ? topMunicipios.size() : k;
    unsigned d = k == 0 ? topDistritos.size() : k;
    cout << "Top de municípios tendo em conta as suas necessidades de transportes:" << endl;
    for (unsigned i = 1; i <= m; i++) {
        cout << i << ". " << topMunicipios.top().second << " (soma do fluxo entre todos os pares de estações: " << topMunicipios.top().first << ")" << endl;
        topMunicipios.pop();
    }
    cout << endl;
    cout << "Top de distritos tendo em conta as suas necessidades de transportes:" << endl;
    for (unsigned j = 1; j <= d; j++) {
        cout << j << ". " << topDistritos.top().second << " (soma do fluxo entre todos os pares de estações: " << topDistritos.top().first << ")" << endl;
        topDistritos.pop();
    }
}

void Management::fluxoMaximoChegada() {
    verificarFicheirosDados();
    cout << "Estação de Chegada" << endl;
    Station station = readStation();
    network.addSuperSource(station.getId());
    network.edmondsKarp(0, station.getId());
    unsigned flow = network.getFlow(station.getId());
    cout << "O número máximo de comboios que podem chegar simultaneamente a " << station.getName() << " é " << flow << endl;
    network.removeSuperSource();
}

void Management::custoMinimo() {
    verificarFicheirosDados();
    cout << "Estação A" << endl;
    Station source = readStation();
    cout << "Estação B" << endl;
    Station target = readStation();
    network.dijkstra(source.getId());
    unsigned flow = network.getPathFlow(target.getId());
    if (flow == 0)
        cout << "Não é possível viajar entre " << source.getName() << " e " << target.getName() << endl;
    else {
        unsigned cost = network.getPathCost(target.getId(), flow);
        cout << "O custo mínimo da viagem entre " << source.getName() << " e " << target.getName() << " é " << cost << "€" << ", para um máximo de " << flow << " comboios em simultâneo." << endl;
    }
}

void Management::conetividadeReduzida() {
    verificarFicheirosDados();
    cout << "Introduza o número de segmentos a remover para reduzir a conetividade do grafo original: ";
    unsigned n = readInt();
    for (int i = 1; i <= n; i++) {
        cout << "Segmento " << i << "." << endl;
        removeSegment();
    }
    cout << "Estações para calcular o número máximo de comboios que podem viajar entre elas (com conetividade reduzida)" << endl;
    calcularFluxoMaximo(network);
    lerFicheirosDados(true);
}

void Management::topAfetadas() {
    verificarFicheirosDados();
    vector<pair<unsigned, Station>> flows;
    for (const auto &station : stations) {
        network.addSuperSource(station.getId());
        network.edmondsKarp(0, station.getId());
        flows.emplace_back(network.getFlow(station.getId()), station);
        network.removeSuperSource();
    }
    cout << "Segmento a remover" << endl;
    removeSegment();
    cout << "Remoção de segmento bem-sucedida!" << endl;
    priority_queue<pair<double, string>> topDiferenca;
    for (const auto &pair : flows) {
        int stationId = pair.second.getId();
        network.addSuperSource(stationId);
        network.edmondsKarp(0, stationId);
        unsigned flow = network.getFlow(stationId);
        double diferenca = pair.first != 0 ? (double) (100 * (pair.first - flow)/pair.first) : 0.0;
        topDiferenca.push(make_pair(diferenca, pair.second.getName()));
        network.removeSuperSource();
    }
    cout << "Introduza o valor de K (0 para um top completo, com todas as estações afetadas): ";
    unsigned k = readInt();
    if (k == 0)
        k = topDiferenca.size();
    cout << "Top de estações mais afetadas:" << endl;
    for (unsigned i = 1; i <= k; i++) {
        cout << i << ". " << topDiferenca.top().second << " (redução de " << setprecision(3) << topDiferenca.top().first << "% no número de comboios)" << endl;
        if (topDiferenca.top().first == 0.0) {
            cout << "..." << endl << "Todas as estações restantes não são afetadas" << endl;
            break;
        }
        topDiferenca.pop();
    }
    lerFicheirosDados(true);
}
