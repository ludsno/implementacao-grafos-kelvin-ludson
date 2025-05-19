#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <string>

#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int n, int s, const vector<vector<pair<int, int>>> &adj, vector<int> &dist, vector<int> &pre)
{
    dist.assign(n, INF);
    pre.assign(n, -1);
    dist[s] = 0;

    // Fila de prioridade (min-heap) para armazenar os vértices e as distâncias
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty())
    {
        int u = pq.top().second; // Vértice com a menor distância
        int d = pq.top().first;  // Distância mínima atual
        pq.pop();

        // Ignorar se a distância atual for maior que a registrada
        if (d > dist[u])
            continue;

        // Relaxar as arestas do vértice u
        for (const auto &edge : adj[u])
        {
            int v = edge.first;  // Vértice vizinho
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

    // if (inputFile.empty() || startVertex == -1)
    if (inputFile.empty())
    {
        cerr << "Erro: parâmetro -f <arquivo> não fornecido. Use -h para ajuda.\n";
        return 1;
    }
    if (startVertex == -1)
        startVertex = 1;

    ifstream inFile(inputFile);
    if (!inFile)
    {
        cerr << "Erro: não foi possível abrir o arquivo de entrada.\n";
        return 1;
    }

    int n, m;
    inFile >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        inFile >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
        adj[v - 1].emplace_back(u - 1, w);
    }
    inFile.close();

    vector<int> dist(n, INF), pre(n, -1);
    dijkstra(n, startVertex - 1, adj, dist, pre);

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

    for (int i = 0; i < n; ++i)
    {
        out << i + 1 << ":" << (dist[i] == INF ? -1 : dist[i]);
        if (i != n - 1) out << " ";
    }
    out << "\n";

    if (outFile.is_open())
        outFile.close();

    return 0;
}