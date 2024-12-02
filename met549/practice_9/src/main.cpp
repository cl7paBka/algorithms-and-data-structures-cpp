#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;
const int inf = numeric_limits<int>::max();
struct Point {
    int to;
    int weight;
};
class Graph {
public:
    Graph(int vertices) : dolist(vertices) {}
    void addPoint(int u, int v, int weight) {
        dolist[u].push_back({v, weight});
        dolist[v].push_back({u, weight});
    }
    vector<int> dijkstra(int start) {
        vector<int> distances(dolist.size(), inf);
        distances[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});
        while (!pq.empty()) {
            int current_distance = pq.top().first;
            int current_vertex = pq.top().second;
            pq.pop();
            if (current_distance > distances[current_vertex]) {
                continue;
            }
            for (const Point& point : dolist[current_vertex]) {
                int distance = current_distance + point.weight;
                if (distance < distances[point.to]) {
                    distances[point.to] = distance;
                    pq.push({distance, point.to});
                }
            }
        }
        return distances;
    }
private:
    vector<vector<Point>> dolist;
};
int main() {
    setlocale(LC_ALL, "Russian");
    const int numVert = 5;
    Graph gr(numVert);
    gr.addPoint(0, 1, 5);
    gr.addPoint(0, 2, 3);
    gr.addPoint(0, 3, 4);
    gr.addPoint(0, 4, 4);
    gr.addPoint(1, 2, 3);
    gr.addPoint(1, 3, 5);
    gr.addPoint(1, 4, 6);
    gr.addPoint(2, 3, 4);
    gr.addPoint(2, 4, 7);
    gr.addPoint(3, 4, 7);
    vector<int> vertices {1, 2, 3, 4};
    int minDist = inf;
    vector<vector<int>> bestRoutes;
    do {
        int current = 0;
        int start = 0;
        vector<int> distances = gr.dijkstra(start);
        current += distances[vertices[0]];
        for (size_t i = 0; i < vertices.size() - 1; i++) {
            distances = gr.dijkstra(vertices[i]);
            current += distances[vertices[i + 1]];
        }
        distances = gr.dijkstra(vertices.back());
        current += distances[start];
        cout << "Маршрут: П -> ";
        for (size_t i = 0; i < vertices.size(); i++) {
            cout << "ОС-" << vertices[i] << (i < vertices.size() - 1 ? " => " : " => П");
        }
        cout << " | Расстояние: " << current << " км" << endl;

        if (current < minDist) {
            minDist = current;
            bestRoutes.clear();
            bestRoutes.push_back(vertices);
        } else if (current == minDist) {
            bestRoutes.push_back(vertices);}
    } while (next_permutation(vertices.begin(), vertices.end()));
    cout << "Наименьшее расстояние: " << minDist << " км" << endl;
    cout << "Кратчайшие пути: " << endl;
    for (const auto& route : bestRoutes) {
        cout << "П -> ";
        for (size_t i = 0; i < route.size(); i++) {
            cout << "ОС-" << route[i] << (i < route.size() - 1 ? " -> " : " -> П");}
        cout << endl;
    }
    return 0;
}

