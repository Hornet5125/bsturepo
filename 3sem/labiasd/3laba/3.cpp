#include <iostream>
using namespace std;
const int INF = 1'000'000'000;
struct Edge {
    int u, v, weight;
};
void print_graph(int** weight, int n) {
    cout << "Матрица весов (INF - ребра нет):\n     ";
    for (int j = 0; j < n; ++j) {
        cout << (char)('A' + j) << "\t";
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        cout << (char)('A' + i) << "\t";
        for (int j = 0; j < n; ++j) {
            if (weight[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << weight[i][j] << "\t";
            }
        }
        cout << '\n';
    }
}
long long prima(int** weight, int n, int start, Edge* result, int& result_count) {
    bool* used = new bool[n];
    int* best = new int[n];
    int* parent = new int[n];
    for (int i = 0; i < n; ++i) {
        used[i] = false;
        best[i] = INF;
        parent[i] = -1;
    }
    used[start] = true;
    best[start] = 0;
    for (int i = 0; i < n; ++i) {
        if (weight[start][i] != INF) {
            best[i] = weight[start][i];
            parent[i] = start;
        }
    }
    result_count = 0;
    long long total = 0;
    cout << "\nШаги алгоритма Прима (старт из вершины " << (char)('A' + start) << "):\n";
    cout << "Шаг 0: в дереве только вершина " << (char)('A' + start) << '\n';
    for (int step = 1; step < n; ++step) {
        int v = -1;
        for (int i = 0; i < n; ++i) {
            if (!used[i] && best[i] != INF &&
                (v == -1 || best[i] < best[v])) {
                v = i;
            }
        }
        if (v == -1) {
            cout << "Граф несвязный: остовного дерева не существует\n";
            break;
        }
        used[v] = true;
        total += best[v];
        result[result_count].u = parent[v];
        result[result_count].v = v;
        result[result_count].weight = best[v];
        ++result_count;
        cout << "Шаг " << step << ": ближайшая вершина " << (char)('A' + v)
             << ", добавлено ребро " << (char)('A' + parent[v])
             << " - " << (char)('A' + v) << " (вес " << best[v]
             << "), сумма весов: " << total << '\n';
        for (int i = 0; i < n; ++i) {
            if (!used[i] && weight[v][i] != INF && weight[v][i] < best[i]) {
                best[i] = weight[v][i];
                parent[i] = v;
            }
        }
    }
    delete[] used;
    delete[] best;
    delete[] parent;
    return total;
}
int main() {
    int n = 7;
    int m = 11;
    Edge* edges = new Edge[m]{
        {0, 3, 5},
        {3, 5, 6},
        {0, 1, 7},
        {1, 4, 7},
        {1, 2, 8},
        {4, 5, 8},
        {3, 1, 9},
        {4, 6, 9},
        {2, 4, 5},
        {5, 6, 11},
        {3, 4, 15}
    };
    int** weight = new int*[n];
    for (int i = 0; i < n; ++i) {
        weight[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            weight[i][j] = INF;
        }
    }
    for (int i = 0; i < m; ++i) {
        weight[edges[i].u][edges[i].v] = edges[i].weight;
        weight[edges[i].v][edges[i].u] = edges[i].weight;
    }
    print_graph(weight, n);
    Edge* mst = new Edge[n - 1];
    int mstCount = 0;
    long long total = prima(weight, n, 0, mst, mstCount);
    cout << "\n РЕЗУЛЬТАТ \n";
    cout << "Рёбра минимального остовного дерева:\n";
    for (int i = 0; i < mstCount; ++i) {
        cout << (char)('A' + mst[i].u) << " - " << (char)('A' + mst[i].v)
             << " : " << mst[i].weight << "\n";
    }
    cout << "Суммарный вес МОД: " << total << "\n";
    for (int i = 0; i < n; ++i) {
        delete[] weight[i];
    }
    delete[] weight;
    delete[] edges;
    delete[] mst;
    return 0;
}
