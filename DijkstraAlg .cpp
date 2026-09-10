template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

min_heap<pair<long long, vector<int>>> pq;
min_heap<pair<long long, int>> pq;

// Dist Array 3D
vector<vector<vector<long long>>> dist(n, vector<vector<long long>>(m, vector<long long>(2, LLONG_MAX)));

// Dist Array 2D
vector<vector<long long>> dist(n, vector<long long>(m, LLONG_MAX));

// Directions
int xd[4] = {0, 1, -1, 0};
int yd[4] = {1, 0, 0, -1};
for (int dr = 0; dr < 4; dr++)
{
    int nx = i + xd[dr];
    int ny = j + yd[dr];

    // 3D
    if (next_cost < dist[nx][ny][np])
    {
        dist[nx][ny][np] = next_cost;
        pq.push({next_cost, {nx, ny, np}});
    }

    // 2D
    if (next_cost < dist[nx][ny])
    {
        dist[nx][ny] = next_cost;
        pq.push({next_cost, {nx, ny}});
    }
}

while (!pq.empty()) {}
