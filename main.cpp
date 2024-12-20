#include <iostream>
#include "grafo.hpp"

int main() {
    int NC, NE;
    std::cin >> NC >> NE;

    Grafo grafo(NC);

    std::vector<std::string> cidades;
    for (int i = 0; i < NE; ++i) {
        std::string cidadeA, cidadeB;
        std::cin >> cidadeA >> cidadeB;
        cidades.push_back(cidadeA);
        cidades.push_back(cidadeB);
    }

    for (const std::string& cidade : cidades) {
        grafo.adicionarCidade(cidade);
    }

    for (int i = 0; i < NE; ++i) {
        std::string cidadeA = cidades[2 * i];
        std::string cidadeB = cidades[2 * i + 1];
        grafo.adicionarEstrada(cidadeA, cidadeB);
    }

    std::string capital = grafo.encontrarCapital();
    std::cout << capital << std::endl;

    auto batalhoesSecundarios = grafo.contarBatalhoesSecundarios();
    std::cout << batalhoesSecundarios.size() << std::endl;
    for (const std::string& cidade : batalhoesSecundarios) {
        std::cout << cidade << std::endl;
    }

    return 0;
}
