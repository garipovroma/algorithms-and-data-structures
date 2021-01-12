#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e3 + 228;

vector <pair<int, int>> g[N];
vector <pair<int, int>> tg[N];
vector <int> ord;
vector <int> used;

int n, m, color = 1;

void tops(int v, int x) {
    used[v] = 1;
    for (auto e : g[v]) {
        int i = e.first;
        int id = e.second;
        if (id > x) {
            continue;
        }
        if (used[i] == -1) {
            tops(i, x);
        }
    }
    ord.push_back(v);
}

void dfs(int v, int dfs_color, int x) {
    used[v] = dfs_color;
    for (auto e : tg[v]) {
        int i = e.first;
        int id = e.second;
        if (id > x) {
            continue;
        }
        if (used[i] == -1) {
            dfs(i, dfs_color, x);
        }
    }
}

bool f(int x) {
    ord.clear();
    used.clear();
    used.resize(2 * n, -1);
    for (int i = 0; i < 2 * n; i++) {
        if (used[i] == -1) {
            tops(i, x);
        }
    }
    reverse(all(ord));
    used.clear();
    used.resize(2 * n, -1);
    for (int i : ord) {
        if (used[i] == -1) {
            dfs(i, color, x);
            color++;
        }
    }
    for (int i = 0; i < n; i++) {
        int x = i, y = i + n;
        if (used[x] == used[y]) {
            return false;
        }
    }
    return true;
}

int main() {
    #ifdef HOME
    freopen("input.txt", "rt", stdin);
    #endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    string edge_str;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b >> edge_str;
        a--;
        b--;
        if (edge_str == "T") {
            g[a].push_back({b, i});
            g[b].push_back({a, i});
            tg[b].push_back({a, i});
            tg[a].push_back({b, i});
        } else {
            g[a].push_back({b + n, i});
			g[b].push_back({a + n, i});
			g[a + n].push_back({b, i});
			g[b + n].push_back({a, i});


			tg[b + n].push_back({a, i});
			tg[a + n].push_back({b, i});
			tg[b].push_back({a + n, i});
			tg[a].push_back({b + n, i});
        }
    }
    int l = 0, r = m;
    while (r - l > 1) {
        int mm = (l + r) / 2;
        if (!f(mm)) {
            r = mm;
        } else {
            l = mm;
        }
    }
    cout << l + 1;
    return 0;
}
