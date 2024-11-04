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
    std::cout << "A capital ideal é: " << capital << std::endl;

    int batalhoesSecundarios = grafo.contarBatalhoesSecundarios();
    std::cout << "Número mínimo de batalhões secundários necessários: " << batalhoesSecundarios << std::endl;

    return 0;
}
