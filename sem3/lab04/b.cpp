#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int INF = 1000000000;
const int N = 100;

struct edge {
    int a, b, c, f, back_edge_id;
};

vector <int> g[N];
vector <edge> ge;
vector <bool> used;

int dfs(int v, int min_cost, int t) {
    if (v == t) {
        return min_cost;
    }
    used[v] = true;
    for (int id : g[v]) {
        int u = ge[id].b;
        int c = ge[id].c;
        int f = ge[id].f;
        if (!used[u] && f < c) {
            int df = dfs(u, min(min_cost, c - f), t);
            if (df > 0) {
                ge[id].f += df;
                ge[ge[id].back_edge_id].f -= df;
                return df;
            }
        }
    }
    return 0;
}
ввфыв
int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        edge edge_0 = {a, b, c, 0, len(ge) + 1};
        edge edge_1 = {b, a, 0, 0, len(ge)};
        g[a].push_back(len(ge));
        ge.push_back(edge_0);
        g[b].push_back(len(ge));
        ge.push_back(edge_1);
    }
    int new_path_min_cost = 228;
    do {
        used.assign(n, false);
        new_path_min_cost = dfs(0, INF, n - 1);
    } while (new_path_min_cost != 0);
    int ans = 0;
    for (int id : g[0]) {
        ans += ge[id].f;
    }
    cout << ans;
    return 0;
}
