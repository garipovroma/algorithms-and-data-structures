#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

struct DSU{
	vector <int> p, sz, mn, mx;
	DSU(int n) {
		p.resize(n);
		sz.resize(n);
		mn.resize(n);
		mx.resize(n);
		for (int i = 0; i < n; i++) {
			p[i] = i;
			sz[i] = 1;
			mn[i] = i;
			mx[i] = i;
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
		//   sz[a] > sz[b]
		if (sz[b] > sz[a]) swap(a, b);
		sz[a] += sz[b];
		p[b] = a;
		mn[a] = min(mn[a], mn[b]);
		mx[a] = max(mx[a], mx[b]);
		return true;
	}
};

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	DSU d(n);
	string type;
	while (cin >> type) {
		if (type == "get") {
			int x;
			cin >> x;
			x--;
			x = d.get_p(x);
			cout << d.mn[x] + 1 << ' ' << d.mx[x] + 1 << ' ' << d.sz[x] << "\n";
		} else {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			d.un(a, b);
		}
	}
	return 0;
}
