#include <iostream>
using namespace std;
const long long INF = 1'000'000'000'000'000LL;
void dijkstra() {
    int n, m;
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;
    long long** graph = new long long*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new long long[n];
        for (int j = 0; j < n; ++j) {
            graph[i][j] = INF;
        }
    }
    cout << "Введите рёбра в формате: начало конец вес\n";
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        --from;
        --to;
        graph[from][to] = weight;
        // Для неориентированного графа раскомментировать:
        // graph[to][from] = weight;
    }
    int start;
    cout << "Введите начальную вершину: ";
    cin >> start;
    --start;
    long long* dist = new long long[n];
    bool* visited = new bool[n];

    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[start] = 0;
    for (int step = 0; step < n; ++step) {
        int v = -1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[i] != INF &&
                (v == -1 || dist[i] < dist[v])) {
                v = i;
            }
        }
        if (v == -1) {
            break;
        }
        visited[v] = true;

        for (int to = 0; to < n; ++to) {
            if (graph[v][to] != INF &&
                dist[v] + graph[v][to] < dist[to]) {
                dist[to] = dist[v] + graph[v][to];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << "Расстояние до вершины " << i + 1 << ": ";
        if (dist[i] == INF) {
            cout << "недостижима";
        } else {
            cout << dist[i];
        }
        cout << '\n';
    }
    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] dist;
    delete[] visited;
}
int main() {
    dijkstra();
    return 0;
}