#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Edge {
    int u, v, weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);

        for (int i = 1; i <= n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
  
        return parent[u];
    }

    bool unite(int u, int v) {
        int pu = find(u), pv = find(v);

        if (pu == pv) {
            return false;
        }

        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        }
        else if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        }
        else {
            parent[pv] = pu;
            rank[pu]++;
        }

        return true;
    }
};

int kruskal(int n, vector<Edge>& edges, vector<Edge>& agm) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    int totalCostWeight = 0;

    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            agm.push_back(e);
            totalCostWeight += e.weight;
        }
    }

    return totalCostWeight;
}

void show_help() {
    cout << "Uso: ./kruskal -f <arquivo> [-o <arquivo>] [-s] [-h]\n";
    cout << "-h           : mostra o help\n";
    cout << "-o <arquivo> : redireciona a saida para o 'arquivo'\n";
    cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada\n";
    cout << "-s           : mostra a solução\n";
}

int main(int argc, char* argv[]) {
    string inputFile, outputFile;
    bool show_solution = false;

    // Parse dos argumentos
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h") {
            show_help();
            return 0;
        } else if (arg == "-f" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (arg == "-s") {
            show_solution = true;
        }
    }

    if (inputFile.empty()) {
        cerr << "Erro: arquivo de entrada não especificado. Use -f <arquivo>\n";
        return 1;
    }

    ifstream infile(inputFile);
    if (!infile) {
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    int n, m;
    infile >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        infile >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    vector<Edge> agm;
    int totalCost = kruskal(n, edges, agm);

    // Redireciona saída
    ostream* out = &cout;
    ofstream fout;

    if (!outputFile.empty()) {
        fout.open(outputFile);
        if (!fout) {
            cerr << "Erro ao abrir o arquivo de saída.\n";
            return 1;
        }
        out = &fout;
    }

    if (show_solution) {
        for (const Edge& e : agm) {
            *out << "(" << e.u << "," << e.v << ") ";
        }
        *out << endl;
    } else {
        *out << totalCost << endl;
    }

    return 0;
}