#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int INF = 2000000000;

int n, m, s, t;

struct edge {
    int from, to, capacity, flow, id;
    edge() {}
    edge(int a, int b, int c, int d) {
        from = a;
        to = b;
        capacity = c;
        flow = d;
    }
    edge(int a, int b, int c, int d, int _id) {
        from = a;
        to = b;
        capacity = c;
        flow = d;
        id = _id;
    }
};

vector <vector <int>> g;
vector <edge> edges;

void add_edge(int a, int b, int c, int id = -1) {
    g[a].push_back(len(edges));
    edges.emplace_back(a, b, c, 0, id);
    g[b].push_back(len(edges));
    edges.emplace_back(b, a, 0, 0, id);
}

vector <int> dist;
vector <int> pos;

bool bfs() {
    queue <int> q;
    dist.assign(n + 2, -1);
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        if (dist[t] != -1) {
            break;
        }
        int v = q.front();
        q.pop();
        for (auto ind : g[v]) {
            edge cur_edge = edges[ind];
            int to = cur_edge.to;
            int f = cur_edge.flow;
            int c = cur_edge.capacity;
            if (dist[to] == -1 && f < c) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return (dist[t] != -1);
}

ll dfs(int v, ll flow) {
    if (flow == 0 || v == t) {
        return flow;
    }
    for (int i = pos[v], id = g[v][i]; pos[v] < len(g[v]); pos[v]++, i++, id = g[v][i]) {
        int to = edges[id].to;
        if (dist[v] + 1 == dist[to]) {
            int res = (int) dfs(to, min(flow, (ll) edges[id].capacity - edges[id].flow));
            if (res > 0) {
                edges[id].flow += res;
                edges[id ^ 1].flow -= res;
                return res;
            }
        }
    }
    return 0;
}

ll dinic_find_max_flow() {
    ll max_flow = 0;
    while (true) {
        bool current_bfs_result = bfs();
        if (!current_bfs_result) {
            break;
        }
        pos.assign(n + 2, 0);
        while (true) {
            ll cur_flow_push = dfs(s, INF);
            if (cur_flow_push == 0) {
                break;
            }
            max_flow += cur_flow_push;
        }
    }
    return max_flow;
}

bool is_complete_matching(int n_l, int n_r, vector <pair<int, int>> &edges_from_input) {
    n = n_l + n_r;
    s = n;
    t = n + 1;
    edges.clear();
    g.clear();
    g.resize(n + 2);
    for (int i = 0; i < len(edges_from_input); i++) {
        int x = edges_from_input[i].first;
        int y = edges_from_input[i].second + n_l;
        add_edge(x, y, 1, i);
    }
    for (int i = 0; i < n_l; i++) {
        add_edge(s, i, 1, i + len(edges_from_input));
    }
    for (int i = 0; i < n_r; i++) {
        add_edge(i + n_l, t, 1, i + len(edges_from_input) + n_l);
    }
    ll max_flow = dinic_find_max_flow();
    return (max_flow == n_l);
}

vector <pair<int, pair<int, int>>> mt_edges;

bool check(int m, int vertexes_count) {
    int l = m;
    int r = len(mt_edges) - 1;
    vector <pair<int, int>> cur_iterations_edges;
    for (int i = l; i <= r; i++) {
        cur_iterations_edges.emplace_back(mt_edges[i].second.first, mt_edges[i].second.second);
    }
    return (is_complete_matching(vertexes_count, vertexes_count, cur_iterations_edges));
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            mt_edges.push_back({x, {i, j}});
        }
    }
    sort(all(mt_edges));
    int l = 0, r = len(mt_edges);
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(m, n)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << mt_edges[l].first;
    return 0;
}
