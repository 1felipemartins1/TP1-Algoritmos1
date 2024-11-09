#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <stack> // Para usar std::stack
#include <utility> // Para std::pair

class Grafo {
public:
    Grafo(int numCidades); // Construtor
    void adicionarEstrada(const std::string& cidadeA, const std::string& cidadeB);
    std::string encontrarCapital(); // Encontra a capital ideal
    void adicionarCidade(const std::string& cidade); // Adiciona cidades sem criar conexões
    std::vector <std::string>  contarBatalhoesSecundarios(); // Conta o número de batalhões secundários necessários

private:
    std::pair<bool, int> bfs(int start); // Busca em largura para verificar acessibilidade
    int numCidades;
    std::unordered_map<std::string, int> city_to_index; // Mapeamento cidade -> índice
    std::vector<std::string> index_to_city; // Mapeamento índice -> cidade
    std::vector<std::vector<int>> adjacencias; // Lista de adjacências
    std::vector<std::vector<int>> adjacenciasTranspostas; // Grafo transposto
    std::vector<int> bfsDistancias(int start);
    void dfsOriginal(int v, std::vector<bool>& visitado, std::stack<int>& pilha);
    void dfsTransposto(int v, std::vector<bool>& visitado, std::vector<int>& componente);
    std::vector<std::vector<int>> encontrarComponentesFortementeConexas(); // Encontra SCCs
};

#endif // GRAFO_HPP
