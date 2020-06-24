#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 10;

vector <int> g[N];
vector <int> way;

void build_way(int v, vector <int> &p) {
    way.clear();
    while (v != -1) {
        way.push_back(v);
        v = p[v];
    }
    reverse(all(way));
}

int furthest_vert(int n, int s) {
    vector <bool> used(n, false);
    vector <int> dist(n, 1e9);
    vector <int> p(n, -1);
    used[s] = true;
    dist[s] = 0;
    queue <int> q;
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i : g[x]) {
            if (!used[i]) {
                dist[i] = dist[x] + 1;
                used[i] = true;
                q.push(i);
                p[i] = x;
            }
        }
    }
    int res = s;
    for (int i = 0; i < n; i++) {
        if (dist[i] > dist[res]) {
            res = i;
        }
    }
    build_way(res, p);
    return res;
}

int find_center(int n) {
    int v1 = furthest_vert(n, 0);
    int v2 = furthest_vert(n, v1);
    v1 += v2;
    int m = len(way);
    return m / 2;
}

vector <bool> used;
vector <int> sz;

const unsigned int P = 139;

bool cmp(const int a, const int b) {
	return (sz[a] < sz[b]);
}

int ord[N];
unsigned long long cur_layer[N];

unsigned long long dfs(int v, int depth) {
    sz[v] = 1;
    used[v] = true;
    int cur_layer_sz = 0;
    for (int i : g[v]) {
        if (!used[i]) {
            cur_layer[cur_layer_sz++] = dfs(i, depth + 1);
            sz[v] += sz[i];
        }
    }
    for (int i = 0; i < cur_layer_sz; i++) {
    	ord[i] = i;
    }
    sort(ord, ord + cur_layer_sz, cmp);
    unsigned long long res = sz[v] * sz[v] * sz[v];
    for (int i = 0; i < cur_layer_sz; i++) {
    	unsigned long long k = (unsigned long long) cur_layer[ord[i]] * cur_layer[ord[i]] * depth;
        res = res * P + k;
    }
    return res;
}

bool solve(int n) {
    if (n == 1) {
        return false;
    }
    if (n == 2) {
    	return false;
    }
    used.resize(n, false);
    sz.resize(n, 0);
    int id = find_center(n);
    int v = way[id - 1];
    used[way[id]] = true;
    unsigned long long hash1 = dfs(v, 0);
    used.clear();
    used.resize(n, false);
    sz.clear();
    sz.resize(n, 0);
    int u = way[id + 1];
    used[way[id]] = true;
    unsigned long long hash2 = dfs(u, 0);
    return (hash1 == hash2 && len(g[way[id]]) == 2);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    bool f = solve(n);
    if (f) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
