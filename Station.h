//
// Created by manue on 15/03/2023.
//

#ifndef RAILWAY_STATION_H
#define RAILWAY_STATION_H


#include <string>

class Station {
public:
    /**Construtor sem parâmetros. Constrói uma estação com todos os atributos vazios.
     * <br>Complexidade Temporal: O(1)
     */
    Station();

    /**Construtor com parâmetro. Sanitiza name e constrói uma estação com esse nome sanitizado e os restantes atributos vazios.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento de name
     * @param name nome (a sanitizar)
     */
    Station(const std::string &name);

    /**Construtor com parâmetros. Sanitiza name e constrói uma estação com esse nome sanitizado (para pesquisa) e por sanitizar (para imprimir), distrito district, concelho municipality, freguesia township, linha line e id id.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento de name
     * @param name nome
     * @param district distrito
     * @param municipality concelho
     * @param township freguesia
     * @param line linha
     * @param id id
     */
    Station(const std::string &name, const std::string &district, const std::string &municipality, const std::string &township, const std::string &line, int id);

    /**Retorna o nome sanitizado da estação.
     * <br>Complexidade Temporal: O(1)
     * @return nome sanitizado da estação
     */
    const std::string &getSanitizedName() const;

    /**Retorna o nome da estação.
     * <br>Complexidade Temporal: O(1)
     * @return nome da estação
     */
    const std::string &getName() const;

    /**Retorna o distrito da estação.
     * <br>Complexidade Temporal: O(1)
     * @return distrito da estação
     */
    const std::string &getDistrict() const;

    /**Retorna o concelho da estação.
     * <br>Complexidade Temporal: O(1)
     * @return concelho da estação
     */
    const std::string &getMunicipality() const;

    /**Retorna o id da estação.
     * <br>Complexidade Temporal: O(1)
     * @return id da estação
     */
    int getId() const;

    /**Compara a estação e rhs quanto ao nome sanitizado.
     * <br>Complexidade Temporal: O(n), sendo n o maior comprimento entre os nomes sanitizados
     * @param rhs estação com a qual comparar
     * @return true se a estação e rhs têm igual nome sanitizado, false caso contrário
     */
    bool operator==(const Station &rhs) const;

    /**Compara a estação e rhs quanto ao nome sanitizado, por ordem lexicográfica.
     * <br>Complexidade Temporal: O(n), sendo n o maior comprimento entre os nomes sanitizados
     * @param rhs estação com a qual comparar
     * @return true se a estação tem nome sanitizado lexicograficamente anterior a rhs, false caso contrário
     */
    bool operator<(const Station &rhs) const;

    /**Imprime o nome, o distrito, o concelho, a freguesia e a linha da estação.
     * <br>Complexidade Temporal: O(1)
     */
    void print() const;

private:
    std::string sanitizedName;
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;
    int id;

    /**Sanitiza str, i. e., remove os caracteres especiais (diacríticos) de str.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento de str
     * @param str string a sanitizar
     * @return str sanitizada
     */
    static std::string sanitize(const std::string &str);
};

struct stationHash {
    /**Função de dispersão para a tabela de dispersão de estações.
     * <br>Complexidade Temporal: O(n), sendo n o comprimento do nome sanitizado
     * @param station estação a mapear
     * @return valor da hash para a estação a mapear
     */
    int operator()(const Station &station) const {
        const std::string& str = station.getSanitizedName();
        int v = 0;
        for (const char &ch : str)
            v = 37*v + ch;
        return v;
    }

    /**Função de igualdade para a tabela de dispersão de estações.
     * <br>Complexidade Temporal: O(n), sendo n o maior comprimento entre os nomes sanitizados
     * @param station1 estação 1
     * @param station2 estação 2
     * @return true se as estações são iguais, false caso contrário
     */
    bool operator()(const Station &station1, const Station &station2) const {
        return station1 == station2;
    }
};


#endif //RAILWAY_STATION_H
