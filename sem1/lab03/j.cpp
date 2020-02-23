#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

ll shlak;

struct DSU {
    vector <int> p, sz, mes, r;
    DSU() {}
    DSU(int n) {
        p.resize(n);
        sz.resize(n);
        mes.resize(n);
        r.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            sz[i] = 1;
            mes[i] = 0;
            r[i] = 0;
        }
    }
    int get_p(int v, ll &sum) {
        sum += mes[v];
        if (p[v] == v) return v;
        int x = get_p(p[v], sum);
        return x;
    }
    void un(int a, int b) {
        a = get_p(a, shlak);
        b = get_p(b, shlak);
        if (a == b) return;
        if (sz[a] > sz[b]) swap(a, b);
        p[a] = b;
        sz[b] += sz[a];
        mes[a] -= mes[b];
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
    ll zerg = 0;
    ll p = 1e6 + 3;
    ll sum = 0;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            ll x;
            cin >> x;
            x = (x + zerg) % (ll)n;
            sum = 0;
            int boss = d.get_p((int)x, sum);
            d.mes[boss]++;
            zerg = (30ll * zerg + 239) % p;
        } else if (t == 2) {
            ll a, b;
            cin >> a >> b;
            a = (a + zerg) % (ll)n;
            b = (b + zerg) % (ll)n;
            if (d.get_p((int)a, shlak) == d.get_p((int)b, shlak)) continue;
            d.un((int)a, (int)b);
            zerg = (13ll * zerg + 11) % p;
        } else if (t == 3) {
            ll x;
            cin >> x;
            x = (x + zerg) % (ll)n;
            sum = 0;
            int boss = d.get_p((int)x, sum);
            boss++;
            cout << sum - d.r[(int)x] << "\n";
            zerg = (zerg * 100500ll + sum - d.r[(int)x]) % p;
            d.r[(int)x] = (int)sum;
        }
    }
    return 0;
}
