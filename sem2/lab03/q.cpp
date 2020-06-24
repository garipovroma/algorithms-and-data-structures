#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

struct heavy_light {
    vector <vector<int>> g;
    vector <int> sz, parent, nxt, depth, way_num, way_size, num, head;
    vector <ll> t, mx, p;
    int cur_way = 0;
    int vert_num = 0;
    int n;
    heavy_light() {}
    heavy_light(vector<vector<int>> &other) {
        n = len(other);
        g.resize(n);
        sz.resize(n, 0);
        parent.resize(n, -1);
        nxt.resize(n, -1);
        depth.resize(n, 0);
        way_num.resize(n, 0);
        num.resize(n, -1);
        way_size.resize(n, 0);
        head.resize(n, 0);
        t.resize(4 * n);
        p.resize(4 * n, 0);
        mx.resize(n, 0);
        g = other;
        dfs(0);
        hld(0);
    }
    void dfs(int v, int p = 0) {
        parent[v] = p;
        sz[v] = 1;
        for (int i : g[v]) {
            if (i != p) {
                depth[i] = depth[v] + 1;
                dfs(i, v);
                sz[v] += sz[i];
                if (nxt[v] == -1 || sz[i] > sz[nxt[v]]) {
                    nxt[v] = i;
                }
            }
        }
    }
    void hld(int v, int p = -1) {
        num[v] = vert_num++;
        way_num[v] = cur_way;
        if (way_size[cur_way] == 0) {
            head[cur_way] = v;
        }
        way_size[cur_way]++;
        if (nxt[v] != -1) {
            hld(nxt[v], v);
        }
        for (int i : g[v]) {
            if (i != p && i != nxt[v]) {
                cur_way++;
                hld(i, v);
            }
        }
    }
    ll get_max(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;
        }
        if (tl == l && tr == r) {
            return t[v];
        } else {
            int tm = (tl + tr) / 2;
            ll v1 = get_max(2 * v, tl, tm, l, min(tm, r));
            ll v2 = get_max(2 * v + 1, tm + 1, tr, max(tm + 1, l), r);
            return max(v1, v2);
        }
    }
    ll get_max(int a, int b) {
        ll res = 0;
        while (way_num[a] != way_num[b]) {
            if (depth[head[way_num[a]]] < depth[head[way_num[b]]]) {
                swap(a, b);
            }
            int start = head[way_num[a]];
            if (num[a] == num[start] + way_size[way_num[a]] - 1) {
                res = max(res, mx[way_num[a]]);
            } else {
                res = max(res, get_max(1, 0, n - 1, num[start], num[a]));
            }
            a = parent[start];
        }
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        res = max(res, get_max(1, 0, n - 1, num[a], num[b]));
        return res;
    }
    void set_val(int v, int tl, int tr, int x, int val) {
        if (tl == tr) {
            t[v] += val;
        } else {
            int tm = (tl + tr) / 2;
            if (x <= tm)
                set_val(2 * v, tl, tm, x, val);
            else
                set_val(2 * v + 1, tm + 1, tr, x, val);
            t[v] = max(t[2 * v], t[2 * v + 1]);
        }
    }
    void modify(int x, int val) {
        set_val(1, 0, n - 1, num[x], val);
        int l = num[head[way_num[x]]];
        int r = l + way_size[way_num[x]] - 1;
        mx[way_num[x]] = get_max(1, 0, n - 1, l, r);
    }
};

vector <vector<int>> g;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    heavy_light hld = heavy_light(g);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;
        if (t == 'G') {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            ll res = hld.get_max(a, b);
            cout << res << "\n";
        } else {
            int x;
            int y;
            cin >> x >> y;
            x--;
            hld.modify(x, y);
        }
    }
    return 0;
}
