#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 10;

vector <int> g[N];
vector <int> used;
vector <int> p;

int cycle_beg = -1, cycle_end = -1;

bool find_cycle(int v) {
    used[v] = 1;
    bool res = false;
    for (int i : g[v]) {
        if (used[i] == 0) {
            res |= find_cycle(i);
            p[i] = v;
        } else if (used[i] == 1) {
            cycle_beg = i;
            res = true;
            cycle_end = v;
        }
    }
    used[v] = 2;
    return res;
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
    used.resize(n, 0);
    p.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            if (find_cycle(i)) {
                vector <int> cycle;
                int cur = cycle_end;
                while (cur != cycle_beg) {
                    cycle.push_back(cur);
                    cur = p[cur];
                }
                cycle.push_back(cur);
                reverse(all(cycle));
                cout << "YES\n";
                for (auto x : cycle)
                    cout << x + 1 << ' ';
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}
