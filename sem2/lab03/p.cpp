#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

struct heavy_light {
    vector <vector<int>> g;
    vector <int> sz, parent, nxt, depth, way_num, was_size, num, head;
    vector <ll> t, sum, p;
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
        was_size.resize(n, 0);
        head.resize(n, 0);
        t.resize(4 * n);
        p.resize(4 * n, 0);
        sum.resize(n, 0);
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
        if (was_size[cur_way] == 0) {
            head[cur_way] = v;
        }
        was_size[cur_way]++;
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
    void push(int v, int l, int r) {
        if (p[v] != 0) {
            int m = (l + r) / 2;
            t[2 * v] += p[v] * (m - l + 1);
            t[2 * v + 1] += p[v] * (r - m - 1 + 1);
            p[2 * v] += p[v];
            p[2 * v + 1] += p[v];
            p[v] = 0;
        }
    }
    void add_on_seg(int v, int tl, int tr, int l, int r, ll y) {
        if (l > r) {
            return;
        }
        if (tl == l && tr == r) {
            p[v] += y;
            t[v] += y * (tr - tl + 1);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        add_on_seg(2 * v, tl, tm, l, min(r, tm), y);
        add_on_seg(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, y);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    ll get_sum(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;
        }
        push(v, tl, tr);
        if (tl == l && tr == r) {
            return t[v];
        } else {
            int tm = (tl + tr) / 2;
            ll v1 = get_sum(2 * v, tl, tm, l, min(tm, r));
            ll v2 = get_sum(2 * v + 1, tm + 1, tr, max(tm + 1, l), r);
            return (v1 + v2);
        }
    }
    ll get_sum(int a, int b) {
        ll res = 0;
        while (way_num[a] != way_num[b]) {
            if (depth[head[way_num[a]]] < depth[head[way_num[b]]]) {
                swap(a, b);
            }
            int start = head[way_num[a]];
            if (num[a] == num[start] + was_size[way_num[a]] - 1) {
                res += sum[way_num[a]];
            } else {
                res += get_sum(1, 0, n - 1, num[start], num[a]);
            }
            a = parent[start];
        }
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        res += get_sum(1, 0, n - 1, num[a], num[b]);
        return res;
    }
    void add_on_path(int a, int b, ll x) {
        while (way_num[a] != way_num[b]) {
            if (depth[head[way_num[a]]] < depth[head[way_num[b]]]) {
                swap(a, b);
            }
            int start = head[way_num[a]];
            if (num[a] == num[start] + was_size[way_num[a]] - 1) {
                //  add_on_seg(1, 0, n - 1, num[start], num[a], x);
                sum[way_num[a]] += x;
            } else {
                add_on_seg(1, 0, n - 1, num[start], num[a], x);
            }
            a = parent[start];
        }
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        add_on_seg(1, 0, n - 1, num[a], num[b], x);
    }
    ll get_val(int v, int tl, int tr, int x) {
        if (tl == tr) {
            return t[v];
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            if (x <= tm)
                return get_val(2 * v, tl, tm, x);
            else
                return get_val(2 * v + 1, tm + 1, tr, x);
        }
    }
    ll get_val(int a) {
        return get_val(1, 0, n - 1, num[a]) + sum[way_num[a]];
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
        if (t == '+') {
            int a, b, x;
            cin >> a >> b >> x;
            a--;
            b--;
            hld.add_on_path(a, b, x);
        } else {
            int x;
            cin >> x;
            x--;
            ll cur = hld.get_val(x);
            cout << cur << "\n";
        }
    }
    return 0;
}
