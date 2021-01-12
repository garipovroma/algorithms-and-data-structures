#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 10;

vector <int> g[N];
vector <int> used;
vector <int> ord;
bool ok = true;

void tops(int v) {
    used[v] = 1;
    for (int i : g[v]) {
        if (used[i] == 0) {
            tops(i);
        } else if (used[i] == 1) {
            ok = false;
        }
    }
    ord.push_back(v);
    used[v] = 2;
}

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
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
    }
    used.resize(n, 0);
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            tops(i);
        }
    }
    if (!ok) {
        cout << -1;
        return 0;
    }
    reverse(all(ord));
    for (int i : ord)
        cout << i + 1 << ' ';
    return 0;
}
