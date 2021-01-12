#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int INF = 2000000000;

int n, m, s, t;

struct edge {
    int to, capacity, flow, id;
    edge() {}
    edge(int b, int c, int d) {
        to = b;
        capacity = c;
        flow = d;
    }
    edge(int b, int c, int d, int _id) {
        to = b;
        capacity = c;
        flow = d;
        id = _id;
    }
};

const int N = 1501;
const int M = 300001;

vector <edge> g[N];

int pos[N], dist[N];
int ans[M];

ll dfs(int v, ll flow) {
    if (flow == 0 || v == t) {
        return flow;
    }
    for (; pos[v] < len(g[v]); pos[v]++) {
        if (dist[v] + 1 == dist[g[v][pos[v]].to]) {
            int res = (int) dfs(g[v][pos[v]].to, min(flow,
            (ll) g[v][pos[v]].capacity - g[v][pos[v]].flow));
            if (res > 0) {
                g[v][pos[v]].flow += res;
                ans[g[v][pos[v]].id] += res;
                return res;
            }
        }
    }
    return 0;
}

ll dinic_find_max_flow() {
    ll max_flow = 0;
    while (true) {
        ll cur_flow_push = dfs(s, INF);
        if (cur_flow_push == 0) {
            break;
        }
        max_flow += cur_flow_push;
        //  memset(pos, 0, sizeof(int) * n);
    }
    return max_flow;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    int l;
    scanf("%d%d%d", &n, &m, &l);
    for (int i = 0; i < n; i++) {
        scanf("%d", &dist[i]);
        dist[i]--;
        if (dist[i] == 0) {
            s = i;
        } else if (dist[i] == l - 1) {
            t = i;
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--;
        b--;
        g[a].emplace_back(b, c, 0, i);
    }
    dinic_find_max_flow();
    for (int i = 0; i < m; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
