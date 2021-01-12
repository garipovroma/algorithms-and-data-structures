#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 501;
const int INF = 2000000000;

int n, m;

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

vector <int> d;
vector <int> pos;

bool bfs() {
    queue <int> q;
    d.assign(n, -1);
    d[0] = 0;
    q.push(0);
    while (!q.empty()) {
        if (d[n - 1] != -1) {
            break;
        }
        int v = q.front();
        q.pop();
        for (auto ind : g[v]) {
            edge cur_edge = edges[ind];
            int to = cur_edge.to;
            int f = cur_edge.flow;
            int c = cur_edge.capacity;
            if (d[to] == -1 && f < c) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    return (d[n - 1] != -1);
}

ll dfs(int v, ll flow) {
    if (flow == 0 || v == n - 1) {
        return flow;
    }
    for (int i = pos[v], id = g[v][i]; pos[v] < len(g[v]); pos[v]++, i++, id = g[v][i]) {
        int to = edges[id].to;
        if (d[v] + 1 == d[to]) {
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
        pos.assign(n, 0);
        while (true) {
            ll cur_flow_push = dfs(0, INF);
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
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        add_edge(a, b, c);
    }

    ll max_flow = dinic_find_max_flow();

    cout << max_flow;
    return 0;
}
