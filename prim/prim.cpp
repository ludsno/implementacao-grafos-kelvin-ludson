#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

struct Edge {
    int end, weight;
};

struct Node {
    int vertex, weight;
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

void showHelp() {
    cout << "Uso: ./prim -f <arquivo> [-o <arquivo>] [-s] [-i <vértice>] [-h]\n";
    cout << "-h           : mostra o help\n";
    cout << "-o <arquivo> : redireciona a saída para o 'arquivo'\n";
    cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada\n";
    cout << "-s           : mostra a solução\n";
    cout << "-i <vértice> : vértice inicial\n";
}

int prim (int numberofVertex, vector<vector<Edge>>& adjacencyList, int startVertex, vector<pair<int, int>>& agm) {
    vector<bool> visited(numberofVertex + 1, false);
    vector<int> minimumCost(numberofVertex + 1, INT_MAX);
    vector<int> parent(numberofVertex + 1, -1);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({startVertex, 0});
    minimumCost[startVertex] = 0;

    int totalCost = 0;

    while (!pq.empty()) {
        int vertex = pq.top().vertex;
        int weight = pq.top().weight;
        pq.pop();

        if (!visited[vertex]) {
            visited[vertex] = true;
            totalCost += weight;

            if (parent[vertex] != -1) {
                agm.push_back({parent[vertex], vertex});
            }

            for (const Edge& edge : adjacencyList[vertex]) {
                int edgeEnd = edge.end;
                int edgeWeight = edge.weight;

                if (!visited[edgeEnd] && edgeWeight < minimumCost[edgeEnd]) {
                    minimumCost[edgeEnd] = edgeWeight;
                    parent[edgeEnd] = edgeWeight;
                    pq.push({edgeEnd, edgeWeight});
                }
            }
        }
    }

    return totalCost;
}


int main(int argc, char* argv[]) {
    string inputFile, outputFile;
    bool showSolution = false;
    int startVertex = 1;

        // Parse dos argumentos
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h") {
            showHelp();
            return 0;
        } else if (arg == "-f" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (arg == "-s") {
            showSolution = true;
        } else if (arg == "-i" && i + 1 < argc) {
            startVertex = stoi(argv[++i]);
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

    int numberofVertex, numberofEdges;
    infile >> numberofVertex >> numberofEdges;

    vector<vector<Edge>> adjacencyList(numberofVertex + 1);

    for (int i = 0; i < numberofEdges; ++i) {
        int vertexU, vertexV, weight;
        infile >> vertexU >> vertexV >> weight;
        adjacencyList[vertexU].push_back({vertexV, weight});
        adjacencyList[vertexV].push_back({vertexU, weight});
    }

    vector<pair<int, int>> agm;
    int totalCost = prim(numberofVertex, adjacencyList, startVertex, agm);

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

    if (showSolution) {
        for (const auto& e : agm) {
            *out << "(" << e.first << "," << e.second << ") ";
        }
        *out << endl;
    } else {
        *out << totalCost << endl;
    }

    return 0;
}