/*

Pseudocódigo do algoritmo de Dijkstra:

Dijsktra (G = (V, E), vert s, w[]) {

    for v in V:
        dist[v] = ∞
        pre[v] = -1
    dist[s] = 0

    H = Fila_prioridade_min(V, dist[])
    while(!H.empty) {
        u = H.front()
        for (v in Neighbors(u)) {
            if (dist[v] > dist[u] + w(u, v)) {
                dist[v] = dist[u] + w(u, v)
                pre[v] = u
                H.increase_priority(v, dist[v])
            }
        }
    }
}

*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <string>

#include <fstream>
#include <cstring>

using namespace std;

const int INF = numeric_limits<int>::max();

/**
 * @brief Implementa o algoritmo de Dijkstra para encontrar os caminhos mais curtos
 *        de um vértice de origem para todos os outros vértices em um grafo ponderado.
 *
 * @param n Número de vértices no grafo.
 * @param s Vértice de origem a partir do qual os caminhos mais curtos serão calculados.
 * @param adj Lista de adjacências representando o grafo. Cada posição `adj[u]` contém
 *            um vetor de pares `(v, w)`, onde `v` é um vértice vizinho de `u` e `w` é
 *            o peso da aresta entre `u` e `v`.
 *
 * @details
 * - O grafo é representado como uma lista de adjacências, onde cada vértice possui uma
 *   lista de seus vizinhos e os pesos das arestas que os conectam.
 * - A função utiliza uma fila de prioridade (min-heap) para processar os vértices com
 *   a menor distância conhecida primeiro.
 * - Durante a execução, as distâncias mínimas são armazenadas no vetor `dist`, e os
 *   predecessores no caminho mais curto são armazenados no vetor `pre`.
 * - Após a execução, os vetores `dist` e `pre` contêm, respectivamente, as menores
 *   distâncias e os predecessores para reconstruir os caminhos mais curtos.
 *
 * @complexity
 * - Tempo: O((V + E) * log(V)), onde V é o número de vértices e E é o número de arestas.
 * - Espaço: O(V + E), devido à lista de adjacências e à fila de prioridade.
 *
 * @example
 * Entrada:
 * - Número de vértices: 5
 * - Número de arestas: 6
 * - Arestas: (0, 1, 2), (0, 2, 4), (1, 2, 1), (1, 3, 7), (2, 4, 3), (3, 4, 1)
 * - Vértice de origem: 0
 *
 * Saída:
 * Distâncias a partir do vértice 0:
 * Vértice 0: 0
 * Vértice 1: 2
 * Vértice 2: 3
 * Vértice 3: 9
 * Vértice 4: 6
 *
 * Predecessores:
 * Vértice 0: -1
 * Vértice 1: 0
 * Vértice 2: 1
 * Vértice 3: 1
 * Vértice 4: 2
 */
void dijkstra(int n, int s, const vector<vector<pair<int, int>>> &adj, vector<int> &dist, vector<int> &pre)
{
    dist.assign(n, INF);
    pre.assign(n, -1);
    dist[s] = 0;

    // Fila de prioridade (min-heap) para armazenar os vértices e suas distâncias
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty())
    {
        int u = pq.top().second; // Vértice com menor distância
        int d = pq.top().first;  // Distância mínima atual
        pq.pop();

        // Ignorar se a distância atual for maior que a registrada
        if (d > dist[u])
            continue;

        // Relaxar as arestas do vértice u
        for (const auto &edge : adj[u])
        {
            int v = edge.first; // Vértice vizinho
            int w = edge.second; // Peso da aresta (u, v)
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w; // Atualizar a menor distância
                pre[v] = u;            // Atualizar o predecessor
                pq.push({dist[v], v}); // Inserir o vizinho na fila
            }
        }
    }
}

// Função para exibir o help
void showHelp()
{
    cout << "Uso: ./dijkstra -f <arquivo> -i <vertice> [-o <arquivo>] [-h]\n";
    cout << "-h : mostra esta mensagem de ajuda\n";
    cout << "-f <arquivo> : indica o arquivo que contém o grafo de entrada\n";
    cout << "-i <vertice> : vértice inicial\n";
    cout << "-o <arquivo> : redireciona a saída para o arquivo especificado\n";
}

int main(int argc, char *argv[])
{
    string inputFile, outputFile;
    int startVertex = -1;

    // Processar os argumentos da linha de comando
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            showHelp();
            return 0;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            inputFile = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            startVertex = stoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            outputFile = argv[++i];
        }
    }

    if (inputFile.empty() || startVertex == -1)
    {
        cerr << "Erro: parâmetros obrigatórios não fornecidos. Use -h para ajuda.\n";
        return 1;
    }

    // Abrir o arquivo de entrada
    ifstream inFile(inputFile);
    if (!inFile)
    {
        cerr << "Erro: não foi possível abrir o arquivo de entrada.\n";
        return 1;
    }

    // Ler o grafo do arquivo
    int n, m;
    inFile >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        inFile >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w); // Ajustar para índices baseados em 0
    }
    inFile.close();

    // Executar o algoritmo de Dijkstra
    vector<int> dist(n, INF), pre(n, -1);
    dijkstra(n, startVertex - 1, adj, dist, pre);

    // Redirecionar a saída, se necessário
    ofstream outFile;
    if (!outputFile.empty())
    {
        outFile.open(outputFile);
        if (!outFile)
        {
            cerr << "Erro: não foi possível abrir o arquivo de saída.\n";
            return 1;
        }
    }
    ostream &out = outputFile.empty() ? cout : outFile;

    // Exibir as distâncias
    for (int i = 0; i < n; ++i)
    {
        out << i + 1 << ":" << (dist[i] == INF ? -1 : dist[i]) << " ";
    }
    out << "\n";

    if (outFile.is_open())
        outFile.close();
        
    return 0;
}