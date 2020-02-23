#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

// l - r
// l' = mx
//

struct DSU {
    DSU() {}
    vector <int> p, sz, mn, mx;
    DSU(int n) {
        p.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            sz[i] = 1;
        }
    }
    int get_p(int v) {
        if (p[v] == v)
            return v;
        else
            return p[v] = get_p(p[v]);
    }
    bool un(int a, int b) {
        a = get_p(a);
        b = get_p(b);
        if (a == b) return false;
        if (sz[b] > sz[a]) swap(a, b);
        sz[a] += sz[b];
        p[b] = a;
        return true;
    }
};

struct rDSU {
    vector <int> p;
    DSU anotherDSU;
    rDSU() {}
    rDSU(int n) {
        anotherDSU = DSU(n);
        p.resize(n);
        for (int i = 0; i < n; i++)
            p[i] = i;
    }
    int get_p(int v) {
        return (p[v] == v ? v : (p[v] = get_p(p[v])));
    }
    bool un(int x, int y) {
        int a = get_p(x);
        int b = get_p(y);
        if (a == b) return false;
        p[a] = b;
        return true;
    }
    void unseg(int l, int r) {
        int x = get_p(l);
        for (int i = x; i <= r; i++) {
            int pi = get_p(i);
            anotherDSU.un(pi, r);
            p[i] = r;
            if (pi == r) {
                break;
            }
        }
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    rDSU d(n);
    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        x--;
        y--;
        if (t == 1) {
            d.anotherDSU.un(x, y);
        } else if (t == 2) {
            d.unseg(x, y);
        } else if (t == 3) {
            bool kek = false;
            if (d.anotherDSU.get_p(x) == d.anotherDSU.get_p(y))
                kek = true;
            if (kek)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
    return 0;
}
