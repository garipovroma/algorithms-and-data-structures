#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int INF = 2000000000;
const ll LL_INF = (1ll << 62ll) - 1ll;

int n, m, s, t;

struct edge {
    int from, to, capacity, flow, cost, id;
    edge() {}
    edge(int _from, int _to, int _capacity, int _flow, int _cost, int _id = -1) {
        from = _from;
        to = _to;
        capacity = _capacity;
        flow = _flow;
        cost = _cost;
        id = _id;
    }
};

vector <vector <int>> g;
vector <edge> edges;

void add_edge(int a, int b, int c, int cost = -1, int id = -1) {
    g[a].push_back(len(edges));
    edges.emplace_back(a, b, c, 0, cost, 2 * id);
    g[b].push_back(len(edges));
    edges.emplace_back(b, a, 0, 0, -cost, 2 * id + 1);
}

vector<ll> ford_bellman_dist() {
    vector <ll> bellman_dist(n, -1);
    bellman_dist[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto cur_edge : edges) {
            int from = cur_edge.from;
            int to = cur_edge.to;
            ll cost = (ll) cur_edge.cost;
            if (bellman_dist[from] != -1 && (bellman_dist[from] + cost < bellman_dist[to]
                                             || bellman_dist[to] == -1)) {
                bellman_dist[to] = bellman_dist[from] + cost;
            }
        }
    }
    return bellman_dist;
}

vector <ll> phi;
vector <ll> dijkstra_dist;
vector <int> parent;
vector <int> parent_edge_id;

bool dijkstra() {
    parent.assign(n, -1);
    parent_edge_id.assign(n, -1);
    dijkstra_dist.assign(n, LL_INF);
    dijkstra_dist[s] = 0;
    vector <bool> dijkstra_used(n, false);
    while (true) {
        int v = -1;
        ll v_dist = LL_INF;
        for (int j = 0; j < n; j++) {
            if (dijkstra_dist[j] < v_dist && !dijkstra_used[j]) {
                v_dist = dijkstra_dist[j];
                v = j;
            }
        }
        if (v == -1 || v_dist == LL_INF) {
            break;
        }
        dijkstra_used[v] = true;
        for (int ind : g[v]) {
            edge cur_edge = edges[ind];
            int i = cur_edge.to;
            ll cost = 1ll * cur_edge.cost + phi[v] - phi[i] + v_dist;
            if (cur_edge.capacity > 0 && cost < dijkstra_dist[i]) {
                dijkstra_dist[i] = cost;
                parent[i] = v;
                parent_edge_id[i] = ind;
            }
        }
    }
    return (dijkstra_dist[t] < LL_INF);
}

ll find_min_cost_max_flow() {
    //  phi = ford_bellman_dist();
    phi = vector<ll>(n, 0);
    ll min_cost_max_flow = 0;
    while (dijkstra()) {
        int push = INF;
        for (int v = t; v != s; v = parent[v]) {
            int id = parent_edge_id[v];
            int capacity = edges[id].capacity;
            push = min(push, capacity);
        }
        for (int v = t; v != s; v = parent[v]) {
            int id = parent_edge_id[v];
            edges[id].capacity -= push;
            edges[id ^ 1].capacity += push;
            min_cost_max_flow += 1ll * edges[id].cost * 1ll * push;
        }
        for (int i = 0; i < n; i++) {
            phi[i] = min(LL_INF, phi[i] + dijkstra_dist[i]);
        }
    }
    return min_cost_max_flow;
}

vector <int> get_min_cost_argmin() {
    vector <int> argmin((n - 2) / 2, -1);
    for (edge cur_edge : edges) {
        if (cur_edge.from == s || cur_edge.to == s || cur_edge.from == t || cur_edge.to == t) {
            continue;
        }
        if (cur_edge.capacity == 0 && cur_edge.id % 2 == 0) {
            int x = cur_edge.from;
            int y = cur_edge.to - (n - 2) / 2;
            argmin[x] = y;
        }
    }
    return argmin;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    vector <vector<int>> a(n, vector<int>(n));
    g.resize(2 * n + 2);
    s = 2 * n;
    t = 2 * n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            add_edge(i, n + j, 1, a[i][j], i * n + j);
        }
    }
    for (int i = 0; i < n; i++) {
        add_edge(s, i, 1, 0, n * (n - 1) / 2 + i);
    }
    for (int i = 0; i < n; i++) {
        add_edge(n + i, t, 1, 0, n * (n - 1) / 2 + n + i);
    }
    n = 2 * n + 2;
    ll ans = find_min_cost_max_flow();
    vector <int> argmin = get_min_cost_argmin();
    cout << ans << "\n";
    for (int i = 0; i < (n - 2) / 2; i++) {
        cout << i + 1 << ' ' << argmin[i] + 1 << "\n";
    }
    return 0;
}
