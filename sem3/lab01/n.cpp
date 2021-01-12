#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1001;

int gr[N][N];
vector <vector<int>> g;
vector <vector<int>> tg;
vector <int> used;
vector <int> ord;

int col = 1, n;

void tops(int v) {
    used[v] = 1;
    for (int i : g[v]) {
        if (used[i] == 0) {
            tops(i);
        }
    }
    ord.push_back(v);
}

void dfs(int v) {
    used[v] = col;
    for (int i : tg[v]) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
}

int cond() {
    col = 1;
    ord.clear();
    used.clear();
    used.resize(n, 0);
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            tops(i);
        }
    }
    reverse(all(ord));
    used.clear();
    used.resize(n, 0);
    for (int i : ord) {
        if (used[i] == 0) {
            dfs(i);
            col++;
        }
    }
    return (col - 1);
}

bool f(int x) {
    g.clear();
    tg.clear();
    g.resize(n);
    tg.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (gr[i][j] <= x) {
                g[i].push_back(j);
                tg[j].push_back(i);
            }
        }
    }
    int cnt = cond();
    return (cnt == 1);
}

int main() {
    #ifdef HOME
    freopen("input.txt", "rt", stdin);
    #endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> gr[i][j];
            r = max(r, gr[i][j]);
        }
    }
    while (r - l > 1) {
        int m = (l + r) / 2;
        bool cur = f(m);
        if (cur) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
    return 0;
}
