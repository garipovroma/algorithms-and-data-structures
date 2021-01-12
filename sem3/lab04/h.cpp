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
    edges.emplace_back(a, b, c, 0, cost, id);
    g[b].push_back(len(edges));
    edges.emplace_back(b, a, 0, 0, -cost, id);
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
    set <pair<ll, int>> dijkstra_set;
    for (int i = 0; i < n; i++) {
        dijkstra_set.insert({dijkstra_dist[i], i});
    }
    while (!dijkstra_set.empty()) {
        auto cur_pair = *dijkstra_set.begin();
        int v = cur_pair.second;
        ll v_dist = cur_pair.first;
        dijkstra_set.erase(dijkstra_set.begin());
        if (v_dist == LL_INF) {
            continue;
        }
        for (int ind : g[v]) {
            edge cur_edge = edges[ind];
            int i = cur_edge.to;
            ll cost = 1ll * cur_edge.cost + phi[v] - phi[i] + v_dist;
            if (cur_edge.capacity > 0 && cost < dijkstra_dist[i]) {
                dijkstra_set.erase({dijkstra_dist[i], i});
                dijkstra_dist[i] = cost;
                dijkstra_set.insert({dijkstra_dist[i], i});
                parent[i] = v;
                parent_edge_id[i] = ind;
            }
        }
    }
    return (dijkstra_dist[t] < LL_INF);
}

ll find_min_cost_max_flow() {
    phi = ford_bellman_dist();
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

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--;
        b--;
        add_edge(a, b, c, d);
    }
    s = 0;
    t = n - 1;
    ll ans = find_min_cost_max_flow();
    cout << ans;
    return 0;
}
