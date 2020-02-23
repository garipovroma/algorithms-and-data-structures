#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

struct DSU {
    vector <int> p, sz, f;
    vector <bool> used;
    int n;
    DSU() {}
    DSU(int nn) {
        p.resize(2 * nn);
        sz.resize(2 * nn);
        used.resize(2 * nn, false);
        f.resize(2 * nn);
        n = nn;
        for (int i = 0; i < 2 * nn; i++) {
            sz[i] = 1;
            //   p[i] = mx[i] = mn[i] = i;
            p[i] = i;
            f[i] = i + 1;
        }
        f[n - 1] = 0;
    }
    int get_p(int v) {
        /*if (p[v] == v)
            return v;
        else
            return (p[v] = get_p(p[v]));*/
          return (p[v] == v ? v : p[v] = get_p(p[v]));
    }
    int un(int x, int y) {  //  x < y
        if (x > y) swap(x, y);
        int a = x, b = y;
        x = get_p(x);
        y = get_p(y);
        //  cout << "(" << x << ", " << y << ") ";
        if (x == y) return -1;
        if (a + 1 == b) {
            f[y] = f[y];
            f[x] = f[y];
        } else if (a == 0 && b == n - 1) {
            f[y] = f[x];
            f[x] = f[y];
        }
        if (sz[x] > sz[y]) swap(x, y);   //  sz[x] < sz[y]
        p[x] = y;
        sz[y] += sz[x];
        return 1;
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    DSU d(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        int xx = d.get_p(x);
        //  cout << xx << ' ' << d.used[x] << ' ' << d.sz[xx] << ' ' << endl;
        //  cout << i << " : " << x << ' ';
        if (d.used[x]) {
            int pos1 = d.f[xx];
            if (pos1 >= n) pos1 -= n;
            d.used[pos1] = true;
            cout << pos1 + 1 << ' ';
            if (pos1 == 0 && d.used[n - 1])
                d.un(pos1, n - 1);
            else if (pos1 != 0 && d.used[pos1 - 1])
                d.un(pos1, pos1 - 1);
            if (pos1 == n - 1 && d.used[0])
                d.un(pos1, 0);
            else if (pos1 != n - 1 && d.used[pos1 + 1])
                d.un(pos1 + 1, pos1);
            //  cout << "ANS = " << pos1 + 1 << ' ';
        } else {
            d.used[x] = true;
            cout << x + 1 << ' ';
            if (x == 0 && d.used[n - 1])
                d.un(x, n - 1);
            else if (x != 0 && d.used[x - 1])
                d.un(x, x - 1);
            if (x == n - 1 && d.used[0])
                d.un(x, 0);
            else if (x != n - 1 && d.used[x + 1])
                d.un(x + 1, x);

            //  cout << "ANS = " << x + 1 << ' ';
            //  continue;
        }
    }
    return 0;
}
