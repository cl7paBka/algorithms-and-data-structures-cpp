#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Graph {
    int V; // Число вершин (включая почтамт и отделения)
    vector<vector<int>> adjMatrix; // Матрица смежности для хранения расстояний между вершинами

    Graph(int V) : V(V), adjMatrix(V, vector<int>(V, INF)) {}

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // Граф неориентированный
    }

    // Реализация алгоритма Дейкстры для нахождения кратчайшего пути от вершины start
    vector<int> dijkstra(int start) {
        vector<int> dist(V, INF); // массив расстояний от start до всех вершин
        vector<bool> visited(V, false); // массив для отслеживания посещенных вершин
        dist[start] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;
            // Находим не посещенную вершину с минимальным расстоянием
            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INF) break;

            visited[u] = true;
            // Обновляем расстояния до соседних вершин
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }
        return dist;
    }

    // Рекурсивная функция для нахождения минимального маршрута коммивояжера
    int travelingSalesman(int pos, int visited, vector<vector<int>>& dp, const vector<vector<int>>& distMatrix, vector<int>& path, vector<int>& bestPath) {
        if (visited == (1 << V) - 1) { // если все вершины посещены
            path.push_back(0); // возвращаемся в почтамт
            int routeLen = distMatrix[pos][0];
            if (routeLen < INF) bestPath = path; // сохраняем путь
            path.pop_back();
            return routeLen; // возвращаемся в почтамт
        }

        if (dp[pos][visited] != -1)
            return dp[pos][visited];

        int ans = INF;
        for (int city = 0; city < V; city++) {
            if ((visited & (1 << city)) == 0) { // если город ещё не посещен
                path.push_back(city);
                int newAns = distMatrix[pos][city] + travelingSalesman(city, visited | (1 << city), dp, distMatrix, path, bestPath);
                if (newAns < ans) {
                    ans = newAns;
                    bestPath = path; // сохраняем текущий лучший путь
                }
                path.pop_back();
            }
        }
        return dp[pos][visited] = ans;
    }
};

int main() {
    int V = 5; // 1 почтамт и 4 отделения связи
    Graph g(V);

    // Заданные расстояния (неориентированный граф)
    g.addEdge(0, 1, 5); // П-1
    g.addEdge(0, 2, 3); // П-2
    g.addEdge(0, 3, 4); // П-3
    g.addEdge(0, 4, 4); // П-4
    g.addEdge(1, 2, 3); // 1-2
    g.addEdge(1, 3, 5); // 1-3
    g.addEdge(1, 4, 6); // 1-4
    g.addEdge(2, 3, 4); // 2-3
    g.addEdge(2, 4, 7); // 2-4
    g.addEdge(3, 4, 7); // 3-4

    // Находим кратчайшие расстояния между всеми парами вершин с помощью алгоритма Дейкстры
    vector<vector<int>> distMatrix(V, vector<int>(V));
    for (int i = 0; i < V; i++) {
        distMatrix[i] = g.dijkstra(i);
    }

    // Инициализация для поиска минимального маршрута
    vector<vector<int>> dp(V, vector<int>(1 << V, -1));
    vector<int> path = {0}; // путь начинается с почтамта (вершина 0)
    vector<int> bestPath; // для хранения наилучшего пути

    int shortestPath = g.travelingSalesman(0, 1, dp, distMatrix, path, bestPath);

    // Выводим результаты
    cout << "Кратчайший маршрут для машины: " << shortestPath << " км" << endl;
    cout << "Последовательность движения: ";
    for (int i = 0; i < bestPath.size(); ++i) {
        if (bestPath[i] == 0 && i != 0 && i != bestPath.size() - 1) {
            cout << "Почтамт -> "; // выводим "Почтамт" для начальной и конечной позиции
        } else if (bestPath[i] == 0) {
            cout << "Почтамт";
        } else {
            cout << "ОС-" << bestPath[i];
        }

        if (i != bestPath.size() - 1) cout << " -> ";
    }
    cout << " -> Почтамт" << endl;

    return 0;
}
