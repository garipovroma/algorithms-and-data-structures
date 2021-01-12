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

void dfs(int v, vector <bool> &used, vector <int> &matching,
         unordered_set<int> &subset, bool right) {
    used[v] = true;
    if (!right) {
        if (matching[v] == -1) {
            return;
        }
        dfs(matching[v], used, matching, subset, !right);
        return;
    }
    subset.insert(v);
    for (int ind : g[v]) {
        int i = edges[ind].to;
        if (i != s && i != t) {
            if (used[i]) {
                continue;
            }
            if (!used[i]) {
                dfs(i, used, matching, subset, !right);
            }
        }
    }
}

void solve(int n_l, int n_r, vector <pair<int, int>> &edges_from_input) {
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
    dinic_find_max_flow();
    vector <int> matching(n, -1);
    for (edge cur_edge : edges) {
        if (cur_edge.from != s && cur_edge.to != s && cur_edge.from != t && cur_edge.to != t) {
            if (cur_edge.flow > 0) {
                int x = cur_edge.from;
                int y = cur_edge.to;
                matching[x] = y;
                matching[y] = x;
            }
        }
    }
    int found_vertex = -1;
    for (int i = n_l; i < n_l + n_r; i++) {
        if (matching[i] == -1) {
            found_vertex = i;
            break;
        }
    }
    if (found_vertex == -1) {
        cout << "0\n\n";
        return;
    }
    unordered_set <int> subset;
    vector <bool> used;
    used.assign(n, false);
    dfs(found_vertex, used, matching, subset, true);
    cout << len(subset) << "\n";
    for (int i : subset) {
        cout << i + 1 - n_l << ' ';
    }
    cout << "\n\n";
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n_l, n_r;
    while (cin >> n_l >> n_r) {
        int m;
        cin >> m;
        vector <pair<int, int>> edges_from_input;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            edges_from_input.emplace_back(a, b);
        }
        solve(n_l, n_r, edges_from_input);
    }
    return 0;
}
