#include <iostream>
using namespace std;
struct Edge {
    int u, v, weight;
};
struct DSU {
    int* parent;
    int* rank;
    int  n;
    void init(int count) {
        n = count;
        parent = new int[n];
        rank   = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i]   = 0;
        }
    }
    void destroy() {
        delete[] parent;
        delete[] rank;
    }
    int find(int x) {
        int root = x;
        while (parent[root] != root)
            root = parent[root];
        while (parent[x] != root) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        return root;
    }
    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false;

        if (rank[rx] < rank[ry]) { int t = rx; rx = ry; ry = t; }
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) ++rank[rx];
        return true;
    }
};
void sort_edges(Edge* edges, int m) {
    for (int i = 1; i < m; ++i) {
        Edge key = edges[i];
        int j = i - 1;
        while (j >= 0 && edges[j].weight > key.weight) {
            edges[j + 1] = edges[j];
            --j;
        }
        edges[j + 1] = key;
    }
}
long long kruskal(int n, Edge* edges, int m, Edge* result, int& mst_count) {
    sort_edges(edges, m);
    DSU dsu;
    dsu.init(n);
    mst_count = 0;
    long long total = 0;
    for (int i = 0; i < m && mst_count < n - 1; ++i) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            result[mst_count++] = edges[i];
            total += edges[i].weight;
        }
    }
    dsu.destroy();
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
    Edge* mst = new Edge[n > 0 ? n - 1 : 0];
    int mstCount = 0;
    long long total = kruskal(n, edges, m, mst, mstCount);
    cout << "Шаги алгоритма Краскала (отсортированные рёбра):\n";
    Edge* sorted_edges = new Edge[m];
    for (int i = 0; i < m; ++i) sorted_edges[i] = edges[i];
    sort_edges(sorted_edges, m);
    DSU dsu;
    dsu.init(n);
    for (int i = 0; i < m; ++i) {
        Edge e = sorted_edges[i];
        cout << "Ребро " << (char)('A' + e.u) << " - " << (char)('A' + e.v) << " (вес " << e.weight << "): ";
        if (dsu.unite(e.u, e.v)) {
            cout << "[ДОБАВЛЕНО]\n";
        } else {
            cout << "[ОТБРОШЕНО - цикл!]\n";
        }
    }
    dsu.destroy();
    delete[] sorted_edges;
    cout << "\n РЕЗУЛЬТАТ \n";
    cout << "Рёбра минимального остовного дерева:\n";
    for (int i = 0; i < mstCount; ++i) {
        cout << (char)('A' + mst[i].u) << " - " << (char)('A' + mst[i].v)
             << " : " << mst[i].weight << "\n";
    }
    cout << "Суммарный вес МОД: " << total << "\n";
    delete[] edges;
    delete[] mst;
    return 0;
}