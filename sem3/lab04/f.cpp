#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 501;
const int INF = 2000000000;

int n, m, s, t;

struct edge {
    int from, to, capacity, flow;
    edge(int a, int b, int c, int d) {
        from = a;
        to = b;
        capacity = c;
        flow = d;
    }
};

vector <int> g[N];
vector <edge> edges;

void add_edge(int a, int b, int c) {
    g[a].push_back(len(edges));
    edges.emplace_back(a, b, c, 0);
    g[b].push_back(len(edges));
    edges.emplace_back(b, a, 0, 0);
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

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    s = n;
    t = n + 1;
    vector <int> lower_capacity(m);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        lower_capacity[i] = c;
        a--;
        b--;
        add_edge(s, b, c);
        add_edge(a, b, d - c);
        add_edge(a, t, c);
    }
    dinic_find_max_flow();
    bool circulation_found = true;
    for (int i = 0; i < len(edges); i++) {
        if (edges[i].from == s) {
            if (edges[i].flow < edges[i].capacity) {
                circulation_found = false;
                break;
            }
        }
    }
    if (!circulation_found) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < len(edges); i += 6) {
        cout << edges[i + 2].flow + lower_capacity[i / 6] << "\n";
    }
    return 0;
}
