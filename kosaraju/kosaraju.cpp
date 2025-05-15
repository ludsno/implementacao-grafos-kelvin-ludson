#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

#include <fstream>
#include <cstring>

using namespace std;

void dfs1(int v, const vector<vector<int>> &adj, vector<bool> &visited, stack<int> &order)
{
    visited[v] = true;
    for (int u : adj[v])
    {
        if (!visited[u])
        {
            dfs1(u, adj, visited, order);
        }
    }
    order.push(v);
}

void dfs2(int v, const vector<vector<int>> &revAdj, vector<bool> &visited, vector<int> &component)
{
    visited[v] = true;
    component.push_back(v);
    for (int u : revAdj[v])
    {
        if (!visited[u])
        {
            dfs2(u, revAdj, visited, component);
        }
    }
}

vector<vector<int>> kosaraju(int n, const vector<vector<int>> &adj)
{
    vector<vector<int>> revAdj(n);
    for (int v = 0; v < n; ++v)
    {
        for (int u : adj[v])
        {
            revAdj[u].push_back(v); // Construir o grafo reverso
        }
    }

    stack<int> order;
    vector<bool> visited(n, false);

    // Passo 1: Realizar a primeira DFS no grafo original para obter a ordem de saída
    for (int v = 0; v < n; ++v)
    {
        if (!visited[v])
        {
            dfs1(v, adj, visited, order);
        }
    }

    // Passo 2: Realizar a DFS no grafo reverso na ordem de saída
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> scc; // Componentes fortemente conexas

    while (!order.empty())
    {
        int v = order.top();
        order.pop();
        if (!visited[v])
        {
            vector<int> component;
            dfs2(v, revAdj, visited, component);
            scc.push_back(component);
        }
    }

    return scc;
}

// Função para exibir o help
void showHelp()
{
    cout << "Uso: ./kosaraju -f <arquivo> -i <vertice> [-o <arquivo>] [-h]\n";
    cout << "-h : mostra esta mensagem de ajuda\n";
    cout << "-f <arquivo> : indica o arquivo que contém o grafo de entrada\n";
    cout << "-o <arquivo> : redireciona a saída para o arquivo especificado\n";
}

int main(int argc, char *argv[])
{

    string inputFile, outputFile;

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
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            outputFile = argv[++i];
        }
    }

    if (inputFile.empty())
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

    int n, m;
    inFile >> n >> m;
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        inFile >> u >> v;
        adj[u - 1].push_back(v - 1); // Ajustar para índices baseados em 0
    }
    inFile.close();

    vector<vector<int>> scc = kosaraju(n, adj);

    cout << "Componentes fortemente conexas:\n";
    for (const auto &component : scc)
    {
        for (int v : component)
        {
            cout << v + 1 << " "; // Ajustar para índices baseados em 1
        }
        cout << "\n";
    }

    return 0;
}
