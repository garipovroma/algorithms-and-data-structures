#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

struct DSU {
    vector <int> p, sz, col;
    DSU() {}
    DSU(int n) {
        p.resize(n);
        sz.resize(n);
        col.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            sz[i] = 1;
            col[i] = 0;
        }
    }
    int get_p(int v) {
        if (p[v] == v) return v;
        int x = get_p(p[v]);
        col[v] += col[p[v]];
        return p[v] = x;
    }
    void un(int a, int b) {
        int x = get_p(a);
        int y = get_p(b);
        if (x == y) return;
        if (sz[x] > sz[y]) {
        	swap(a, b);
        	swap(x, y);
        }
        sz[y] += sz[x];
        p[x] = y;
        if (col[a] % 2 == col[b] % 2)
        	col[x] = col[y] + 1;
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    DSU d(n);
    int shift = 0;
    for (int i = 0; i < m; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        a--;
        b--;
        a = (a + shift) % n;
        b = (b + shift) % n;
        if (t == 0) {
            d.un(a, b);
            /*for (int j = 0; j < n; j++)
                cout << d.col[j] << ' ' ;
            cout << endl;*/
        } else {
        	d.get_p(a);
        	d.get_p(b);
            if ((d.col[a] % 2) == (d.col[b] % 2)) {
                cout << "YES\n";
                shift++;
            }
            else
                cout << "NO\n";
        }
    }
    return 0;
}
