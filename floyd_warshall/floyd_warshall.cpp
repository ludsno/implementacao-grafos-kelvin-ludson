/*

    floyd_warshall(w) {
        dist^0 = w;
        for (k = 1 -> n) {
            for (i = 1 -> n) {
                for (j = 1 -> n) {
                    dist^k[i][j] = min(dist^(k-1)[i][j], dist^(k-1)[i][k] + dist^(k-1)[k][j]);
                }
            }
        }
    }

*/

#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

const long long INF = 1000000000000LL;

void floydWarshall(int n, vector<vector<long long>> &dist)
{
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            if (dist[i][k] == INF)
                continue;
            for (int j = 0; j < n; ++j)
            {
                if (dist[k][j] == INF)
                    continue;
                long long via = dist[i][k] + dist[k][j];
                if (via < dist[i][j])
                    dist[i][j] = via;
            }
        }
    }
}

void printHelp(const char *prog)
{
    cout << "Uso: " << prog << " -f <arquivo> [-o <arquivo>] [-h]\n";
    cout << " -f <arquivo> : arquivo de entrada contendo o grafo\n";
    cout << " -o <arquivo> : (opcional) arquivo de saída\n";
    cout << " -h           : mostra esta mensagem de ajuda\n";
}

int main(int argc, char *argv[])
{
    string inputFile, outputFile;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            printHelp(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            inputFile = argv[++i];
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            outputFile = argv[++i];
        }
    }
    if (inputFile.empty())
    {
        cerr << "Erro: arquivo de entrada não especificado. Use -h para ajuda.\n";
        return 1;
    }
    ifstream inFile(inputFile);
    if (!inFile)
    {
        cerr << "Erro: nao foi possivel abrir o arquivo de entrada.\n";
        return 1;
    }
    int n, m;
    inFile >> n >> m;
    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        inFile >> u >> v >> w;
        dist[u - 1][v - 1] = min(dist[u - 1][v - 1], (long long)w);
    }
    inFile.close();

    floydWarshall(n, dist);

    ofstream outFile;
    ostream &out = outputFile.empty() ? cout : (outFile.open(outputFile), outFile);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            out << (dist[i][j] == INF ? -1 : dist[i][j]);
            if (j + 1 < n)
                out << " ";
        }
        out << "\n";
    }
    if (outFile.is_open())
        outFile.close();
    return 0;
}