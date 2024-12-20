#include "grafo.hpp"
#include <queue>
#include <limits>
#include <iostream>
#include <stack>

Grafo::Grafo(int numCidades) : numCidades(numCidades), adjacencias(numCidades) {
    index_to_city.resize(numCidades);
}

void Grafo::adicionarEstrada(const std::string& cidadeA, const std::string& cidadeB) {
    if (city_to_index.find(cidadeA) == city_to_index.end()) {
        int novoIndice = static_cast<int>(city_to_index.size());
        city_to_index[cidadeA] = novoIndice;
        index_to_city[novoIndice] = cidadeA;
    }
    if (city_to_index.find(cidadeB) == city_to_index.end()) {
        int novoIndice = static_cast<int>(city_to_index.size());
        city_to_index[cidadeB] = novoIndice;
        index_to_city[novoIndice] = cidadeB;
    }
    
    int u = city_to_index[cidadeA];
    int v = city_to_index[cidadeB];
    adjacencias[u].push_back(v);
}

std::pair<bool, int> Grafo::bfs(int start) {
    std::vector<int> dist(numCidades, -1);  
    std::queue<int> fila;
    int alcance = 0;
    int somaDistancias = 0;

    fila.push(start);
    dist[start] = 0;

    while (!fila.empty()) {
        int cidadeAtual = fila.front();
        fila.pop();
        alcance++;

        for (int vizinho : adjacencias[cidadeAtual]) {
            if (dist[vizinho] == -1) { 
                dist[vizinho] = dist[cidadeAtual] + 1;
                somaDistancias += dist[vizinho];
                fila.push(vizinho);
            }
        }
    }

    bool alcancaTodas = (alcance == numCidades);
    return {alcancaTodas, somaDistancias}; 
}

std::string Grafo::encontrarCapital() {
    int melhorCidade = -1;
    int menorSomaDistancias = std::numeric_limits<int>::max();

    for (int i = 0; i < numCidades; ++i) {
        auto [alcancaTodas, somaDistancias] = bfs(i);

        if (alcancaTodas && somaDistancias < menorSomaDistancias) {
            menorSomaDistancias = somaDistancias;
            melhorCidade = i;
        }
    }

    return (melhorCidade != -1) ? index_to_city[melhorCidade] : "Nenhuma capital encontrada";
}

void Grafo::adicionarCidade(const std::string& cidade) {
    if (city_to_index.find(cidade) == city_to_index.end()) {
        int novoIndice = static_cast<int>(city_to_index.size());
        city_to_index[cidade] = novoIndice;
        index_to_city[novoIndice] = cidade;
    }
}

void Grafo::dfsOriginal(int v, std::vector<bool>& visitado, std::stack<int>& pilha) {
    visitado[v] = true;
    for (int vizinho : adjacencias[v]) {
        if (!visitado[vizinho]) {
            dfsOriginal(vizinho, visitado, pilha);
        }
    }
    pilha.push(v);
}

void Grafo::dfsTransposto(int v, std::vector<bool>& visitado, std::vector<int>& componente) {
    visitado[v] = true;
    componente.push_back(v);
    for (int vizinho : adjacenciasTranspostas[v]) {
        if (!visitado[vizinho]) {
            dfsTransposto(vizinho, visitado, componente);
        }
    }
}

std::vector<std::vector<int>> Grafo::encontrarComponentesFortementeConexas() {
    std::stack<int> pilha;
    std::vector<bool> visitado(numCidades, false);
    
    for (int i = 0; i < numCidades; i++) {
        if (!visitado[i]) {
            dfsOriginal(i, visitado, pilha);
        }
    }

    adjacenciasTranspostas.resize(numCidades);
    for (int u = 0; u < numCidades; u++) {
        for (int v : adjacencias[u]) {
            adjacenciasTranspostas[v].push_back(u);
        }
    }

    std::fill(visitado.begin(), visitado.end(), false);
    std::vector<std::vector<int>> sccs;
    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();
        if (!visitado[v]) {
            std::vector<int> componente;
            dfsTransposto(v, visitado, componente);
            sccs.push_back(componente);
        }
    }

    return sccs;
}

// Função para calcular a distância de cada cidade a partir da capital usando BFS
std::vector<int> Grafo::bfsDistancias(int start) {
    std::vector<int> dist(numCidades, std::numeric_limits<int>::max());
    std::queue<int> fila;
    dist[start] = 0;
    fila.push(start);

    while (!fila.empty()) {
        int cidadeAtual = fila.front();
        fila.pop();

        for (int vizinho : adjacencias[cidadeAtual]) {
            if (dist[vizinho] == std::numeric_limits<int>::max()) {
                dist[vizinho] = dist[cidadeAtual] + 1;
                fila.push(vizinho);
            }
        }
    }

    return dist;
}

std::vector<std::string> Grafo::contarBatalhoesSecundarios() {
    auto sccs = encontrarComponentesFortementeConexas();
    std::vector<std::string> batalhoesSecundarios;
    std::string capital = encontrarCapital();
    int capitalIndex = city_to_index[capital];

    // Calcula a distância de cada cidade a partir da capital
    std::vector<int> distancias = bfsDistancias(capitalIndex);

    for (const auto& componente : sccs) {
        bool contemCapital = false;
        int cidadeMaisProxima = -1;
        int menorDistancia = std::numeric_limits<int>::max();

        // Verifica se a SCC contém a capital e encontra a cidade mais próxima
        for (int cidade : componente) {
            if (cidade == capitalIndex) {
                contemCapital = true;
                break;
            }
            // Atualiza a cidade mais próxima se ela tiver uma menor distância
            if (distancias[cidade] < menorDistancia) {
                menorDistancia = distancias[cidade];
                cidadeMaisProxima = cidade;
            }
        }

        // Se a SCC não contém a capital, adiciona a cidade mais próxima na lista de batalhões
        if (!contemCapital && cidadeMaisProxima != -1) {
            batalhoesSecundarios.push_back(index_to_city[cidadeMaisProxima]);
        }
    }

    return batalhoesSecundarios;
}